package currpc

// currpc defines the protobuf message types for the Cursor Connect-RPC protocol.
// These types correspond to the aiserver.v1 protobuf service definitions
// used by the Cursor IDE for streaming chat completions.
//
// The actual protobuf schema is reconstructed from the binary's type information
// and field access patterns in buildCursorRequest and ParseCursorStreamChunk.

import (
	"encoding/binary"
	"fmt"
	"math"
)

// ============================================================================
// Role Constants
// ============================================================================

type Role int32

const (
	RoleUser      Role = 1
	RoleAssistant Role = 2
	RoleTool      Role = 3
)

// ============================================================================
// Message Types
// ============================================================================

// CursorMessage represents a single message in the Cursor conversation.
// Protobuf field mapping (reconstructed from binary offsets):
//   - field 1 (string): MessageID
//   - field 2 (string): Content
//   - field 3 (enum):   Role
type CursorMessage struct {
	MessageID string
	Content   string
	Role      Role
}

// ConversationPart represents a conversation part reference.
// Protobuf field mapping:
//   - field 1 (string):  MessageID
//   - field 2 (enum):    Role
//   - field 3 (message): ToolInfo (optional)
type ConversationPart struct {
	MessageID string
	Role      Role
	ToolInfo  *ToolInfo
}

// ToolInfo represents tool usage information in a conversation part.
// Protobuf field mapping:
//   - field 1 (string): Type
//   - field 2 (string): Name
type ToolInfo struct {
	Type string
	Name string
}

// StreamUnifiedChatRequestWithTools is the top-level request message for
// the StreamChat RPC method.
// Protobuf field mapping (reconstructed from buildCursorRequest):
//   - field 1 (string):   ModelName
//   - field 2 (string):   ConversationID
//   - field 3 (repeated): Messages
//   - field 4 (repeated): ConversationParts
//   - field 5 (string):   SystemPrompt
//   - field 6 (string):   WorkingDirectory
//   - field 7 (string):   WorkspacePath
//   - field 8 (double):   Temperature
//   - field 9 (int32):    MaxTokens
type StreamUnifiedChatRequestWithTools struct {
	ModelName         string
	ConversationID    string
	Messages          []*CursorMessage
	ConversationParts []*ConversationPart
	SystemPrompt      string
	WorkingDirectory  string
	WorkspacePath     string
	Temperature       float64
	MaxTokens         int32
}

// ============================================================================
// Manual Protobuf Marshaling
// ============================================================================

// Marshal serializes a StreamUnifiedChatRequestWithTools to protobuf wire format.
// This is a hand-rolled protobuf encoder since we don't have the .proto file.
func Marshal(req *StreamUnifiedChatRequestWithTools) ([]byte, error) {
	if req == nil {
		return nil, fmt.Errorf("nil request")
	}

	var buf []byte

	// field 1: ModelName (string)
	if req.ModelName != "" {
		buf = appendString(buf, 1, req.ModelName)
	}

	// field 2: ConversationID (string)
	if req.ConversationID != "" {
		buf = appendString(buf, 2, req.ConversationID)
	}

	// field 3: Messages (repeated message)
	for _, msg := range req.Messages {
		msgBytes := marshalCursorMessage(msg)
		buf = appendBytes(buf, 3, msgBytes)
	}

	// field 4: ConversationParts (repeated message)
	for _, part := range req.ConversationParts {
		partBytes := marshalConversationPart(part)
		buf = appendBytes(buf, 4, partBytes)
	}

	// field 5: SystemPrompt (string)
	if req.SystemPrompt != "" {
		buf = appendString(buf, 5, req.SystemPrompt)
	}

	// field 6: WorkingDirectory (string)
	if req.WorkingDirectory != "" {
		buf = appendString(buf, 6, req.WorkingDirectory)
	}

	// field 7: WorkspacePath (string)
	if req.WorkspacePath != "" {
		buf = appendString(buf, 7, req.WorkspacePath)
	}

	// field 8: Temperature (double)
	if req.Temperature != 0 {
		buf = appendDouble(buf, 8, req.Temperature)
	}

	// field 9: MaxTokens (int32)
	if req.MaxTokens != 0 {
		buf = appendVarint(buf, 9, uint64(req.MaxTokens))
	}

	return buf, nil
}

func marshalCursorMessage(msg *CursorMessage) []byte {
	if msg == nil {
		return nil
	}
	var buf []byte

	// field 1: MessageID
	if msg.MessageID != "" {
		buf = appendString(buf, 1, msg.MessageID)
	}
	// field 2: Content
	if msg.Content != "" {
		buf = appendString(buf, 2, msg.Content)
	}
	// field 3: Role (enum/varint)
	if msg.Role != 0 {
		buf = appendVarint(buf, 3, uint64(msg.Role))
	}

	return buf
}

func marshalConversationPart(part *ConversationPart) []byte {
	if part == nil {
		return nil
	}
	var buf []byte

	// field 1: MessageID
	if part.MessageID != "" {
		buf = appendString(buf, 1, part.MessageID)
	}
	// field 2: Role (enum/varint)
	if part.Role != 0 {
		buf = appendVarint(buf, 2, uint64(part.Role))
	}
	// field 3: ToolInfo (message)
	if part.ToolInfo != nil {
		toolBytes := marshalToolInfo(part.ToolInfo)
		buf = appendBytes(buf, 3, toolBytes)
	}

	return buf
}

func marshalToolInfo(info *ToolInfo) []byte {
	if info == nil {
		return nil
	}
	var buf []byte

	if info.Type != "" {
		buf = appendString(buf, 1, info.Type)
	}
	if info.Name != "" {
		buf = appendString(buf, 2, info.Name)
	}

	return buf
}

// ============================================================================
// Protobuf Encoding Primitives
// ============================================================================

// appendTag appends a protobuf field tag (field number + wire type).
func appendTag(buf []byte, fieldNumber uint32, wireType uint32) []byte {
	return appendRawVarint(buf, uint64(fieldNumber<<3|wireType))
}

// appendRawVarint appends a raw varint to the buffer.
func appendRawVarint(buf []byte, v uint64) []byte {
	for v >= 0x80 {
		buf = append(buf, byte(v)|0x80)
		v >>= 7
	}
	buf = append(buf, byte(v))
	return buf
}

// appendVarint appends a varint field (wire type 0).
func appendVarint(buf []byte, fieldNumber uint32, v uint64) []byte {
	buf = appendTag(buf, fieldNumber, 0) // wire type 0 = varint
	buf = appendRawVarint(buf, v)
	return buf
}

// appendString appends a string field (wire type 2 = length-delimited).
func appendString(buf []byte, fieldNumber uint32, s string) []byte {
	buf = appendTag(buf, fieldNumber, 2)
	buf = appendRawVarint(buf, uint64(len(s)))
	buf = append(buf, s...)
	return buf
}

// appendBytes appends a bytes/message field (wire type 2 = length-delimited).
func appendBytes(buf []byte, fieldNumber uint32, data []byte) []byte {
	buf = appendTag(buf, fieldNumber, 2)
	buf = appendRawVarint(buf, uint64(len(data)))
	buf = append(buf, data...)
	return buf
}

// appendDouble appends a double field (wire type 1 = 64-bit).
func appendDouble(buf []byte, fieldNumber uint32, v float64) []byte {
	buf = appendTag(buf, fieldNumber, 1)
	var tmp [8]byte
	binary.LittleEndian.PutUint64(tmp[:], math.Float64bits(v))
	buf = append(buf, tmp[:]...)
	return buf
}
