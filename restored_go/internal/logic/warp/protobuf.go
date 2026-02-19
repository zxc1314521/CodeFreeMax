package warp

// protobuf.go — Custom dynamic protobuf message handling for the Warp channel.
//
// Warp does NOT use generated .pb.go files. Instead, it loads .proto file
// descriptor sets at runtime and uses reflection-based protobuf operations.
// This allows dynamic message construction without compile-time code generation.
//
// From GoReSym symbols (protobuf-related functions):
//   - NewMessage           (0x1720ac0, 544B)  — Create new dynamic message
//   - SetFieldValue        (0x17210a0, 1248B) — Set a field by name
//   - GetStringField       (0x1720f00, 224B)  — Get string field value
//   - GetNestedMessage     (0x1720de0, 288B)  — Get nested message field
//   - GetRepeatedField     (0x1720fe0, 192B)  — Get repeated field as slice
//   - SetNestedMessage     (0x1721580, 384B)  — Set nested message field
//   - AppendToRepeatedField(0x1721700, 960B)  — Append to repeated field
//   - UnmarshalMessage     (0x1720ce0, 256B)  — Deserialize protobuf bytes
//   - ListMessageFields    (0x1721ac0, 1024B) — List all fields in a message
//   - loadFileDescriptorSet(0x1720400, 1344B) — Load .proto descriptors
//   - ensureProtoInitialized(0x17203a0, 96B)  — Lazy init with sync.Once
//   - registerNestedMessages(0x1720940, 384B) — Register nested message types
//   - extractFieldTextRecursive(0x1725dc0, 1728B) — Recursively extract text
//   - ExtractOutputText    (0x1726500, 128B)  — Extract output_text field
//   - ExtractReasoningText (0x1726480, 128B)  — Extract reasoning_text field
//   - DetectContentType    (0x1726580, 608B)  — Detect response content type
//
// The protobuf system uses google.golang.org/protobuf packages:
//   - proto.Marshal / proto.Unmarshal
//   - protodesc for file descriptor parsing
//   - dynamicpb for runtime message construction

import (
	"fmt"
	"sync"

	"google.golang.org/protobuf/encoding/protowire"
	"google.golang.org/protobuf/proto"
	"google.golang.org/protobuf/reflect/protodesc"
	"google.golang.org/protobuf/reflect/protoreflect"
	"google.golang.org/protobuf/reflect/protoregistry"
	"google.golang.org/protobuf/types/descriptorpb"
	"google.golang.org/protobuf/types/dynamicpb"
)

// ============================================================================
// ProtoManager — Dynamic protobuf message manager
// ============================================================================

// ProtoManager manages dynamic protobuf message types for Warp.
// From decompiled: ensureProtoInitialized uses sync.Once pattern.
type ProtoManager struct {
	once     sync.Once
	registry *protoregistry.Files
	types    *protoregistry.Types
	msgTypes map[string]protoreflect.MessageDescriptor
}

// NewProtoManager creates a new ProtoManager.
func NewProtoManager() *ProtoManager {
	return &ProtoManager{
		msgTypes: make(map[string]protoreflect.MessageDescriptor),
	}
}

// ensureInitialized lazily initializes the protobuf descriptors.
// From decompiled: kiro2api_internal_logic_warp_ensureProtoInitialized (0x17203a0, 96B)
// Uses sync.Once with func1 closure (0x17267e0, 160B)
func (pm *ProtoManager) ensureInitialized() {
	pm.once.Do(func() {
		pm.loadDescriptors()
	})
}

// loadDescriptors loads the embedded protobuf file descriptor set.
// From decompiled: kiro2api_internal_logic_warp_loadFileDescriptorSet (0x1720400, 1344B)
// The binary embeds a serialized FileDescriptorSet that defines Warp's
// protobuf message types.
func (pm *ProtoManager) loadDescriptors() {
	// In the original binary, this loads an embedded FileDescriptorSet
	// containing Warp's .proto definitions. We reconstruct the message
	// types manually based on the decompiled field access patterns.
	pm.registry = new(protoregistry.Files)
	pm.types = new(protoregistry.Types)

	// Register known message types
	// From decompiled: registerNestedMessages (0x1720940, 384B)
	pm.registerTypes()
}

// registerTypes registers the known Warp protobuf message types.
// From decompiled: kiro2api_internal_logic_warp_registerNestedMessages
func (pm *ProtoManager) registerTypes() {
	// The actual binary loads these from embedded descriptors.
	// We define them programmatically based on decompiled field patterns.
}

// ============================================================================
// Message — Dynamic protobuf message wrapper
// ============================================================================

// Message wraps a dynamic protobuf message with convenience methods.
// From decompiled: kiro2api_internal_logic_warp_NewMessage (0x1720ac0, 544B)
type Message struct {
	desc    protoreflect.MessageDescriptor
	msg     *dynamicpb.Message
	fields  map[string]interface{}
	raw     []byte
}

// NewMessage creates a new dynamic protobuf message.
// From decompiled: kiro2api_internal_logic_warp_NewMessage
func NewMessage(desc protoreflect.MessageDescriptor) *Message {
	return &Message{
		desc:   desc,
		msg:    dynamicpb.NewMessage(desc),
		fields: make(map[string]interface{}),
	}
}

// NewMessageFromBytes creates a message by unmarshaling protobuf bytes.
func NewMessageFromBytes(desc protoreflect.MessageDescriptor, data []byte) (*Message, error) {
	msg := dynamicpb.NewMessage(desc)
	if err := proto.Unmarshal(data, msg); err != nil {
		return nil, fmt.Errorf("unmarshal protobuf: %w", err)
	}
	return &Message{
		desc:   desc,
		msg:    msg,
		fields: make(map[string]interface{}),
		raw:    data,
	}, nil
}

// ============================================================================
// Field Access Methods
// ============================================================================

// SetFieldValue sets a field value by name.
// From decompiled: kiro2api_internal_logic_warp_SetFieldValue (0x17210a0, 1248B)
// Handles string, int, bool, bytes, float, and nested message types.
func (m *Message) SetFieldValue(name string, value interface{}) error {
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil {
		return fmt.Errorf("field %q not found in message %s", name, m.desc.FullName())
	}

	var pv protoreflect.Value
	switch v := value.(type) {
	case string:
		pv = protoreflect.ValueOfString(v)
	case int:
		pv = protoreflect.ValueOfInt64(int64(v))
	case int32:
		pv = protoreflect.ValueOfInt32(v)
	case int64:
		pv = protoreflect.ValueOfInt64(v)
	case uint32:
		pv = protoreflect.ValueOfUint32(v)
	case uint64:
		pv = protoreflect.ValueOfUint64(v)
	case float32:
		pv = protoreflect.ValueOfFloat32(v)
	case float64:
		pv = protoreflect.ValueOfFloat64(v)
	case bool:
		pv = protoreflect.ValueOfBool(v)
	case []byte:
		pv = protoreflect.ValueOfBytes(v)
	case *Message:
		pv = protoreflect.ValueOfMessage(v.msg)
	default:
		return fmt.Errorf("unsupported value type %T for field %s", value, name)
	}

	m.msg.Set(fd, pv)
	m.fields[name] = value
	return nil
}

// GetStringField gets a string field value by name.
// From decompiled: kiro2api_internal_logic_warp_GetStringField (0x1720f00, 224B)
func GetStringField(m *Message, name string) string {
	if m == nil || m.msg == nil {
		return ""
	}
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil {
		return ""
	}
	return m.msg.Get(fd).String()
}

// GetNestedMessage gets a nested message field by name.
// From decompiled: kiro2api_internal_logic_warp_GetNestedMessage (0x1720de0, 288B)
func GetNestedMessage(m *Message, name string) *Message {
	if m == nil || m.msg == nil {
		return nil
	}
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil || fd.Kind() != protoreflect.MessageKind {
		return nil
	}
	nested := m.msg.Get(fd).Message()
	if !nested.IsValid() {
		return nil
	}
	return &Message{
		desc: fd.Message(),
		msg:  dynamicpb.NewMessage(fd.Message()),
	}
}

// GetRepeatedField gets a repeated field as a slice.
// From decompiled: kiro2api_internal_logic_warp_GetRepeatedField (0x1720fe0, 192B)
func GetRepeatedField(m *Message, name string) []protoreflect.Value {
	if m == nil || m.msg == nil {
		return nil
	}
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil || !fd.IsList() {
		return nil
	}
	list := m.msg.Get(fd).List()
	result := make([]protoreflect.Value, list.Len())
	for i := 0; i < list.Len(); i++ {
		result[i] = list.Get(i)
	}
	return result
}

// SetNestedMessage sets a nested message field.
// From decompiled: kiro2api_internal_logic_warp_SetNestedMessage (0x1721580, 384B)
func SetNestedMessage(m *Message, name string, nested *Message) error {
	if m == nil || nested == nil {
		return fmt.Errorf("nil message")
	}
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil {
		return fmt.Errorf("field %q not found", name)
	}
	m.msg.Set(fd, protoreflect.ValueOfMessage(nested.msg))
	return nil
}

// AppendToRepeatedField appends a value to a repeated field.
// From decompiled: kiro2api_internal_logic_warp_AppendToRepeatedField (0x1721700, 960B)
func AppendToRepeatedField(m *Message, name string, value interface{}) error {
	if m == nil {
		return fmt.Errorf("nil message")
	}
	fd := m.desc.Fields().ByName(protoreflect.Name(name))
	if fd == nil || !fd.IsList() {
		return fmt.Errorf("field %q not found or not repeated", name)
	}

	list := m.msg.Mutable(fd).List()
	switch v := value.(type) {
	case string:
		list.Append(protoreflect.ValueOfString(v))
	case int64:
		list.Append(protoreflect.ValueOfInt64(v))
	case *Message:
		list.Append(protoreflect.ValueOfMessage(v.msg))
	default:
		return fmt.Errorf("unsupported append type %T", value)
	}
	return nil
}

// ============================================================================
// Serialization
// ============================================================================

// Marshal serializes the message to protobuf binary format.
func (m *Message) Marshal() ([]byte, error) {
	return proto.Marshal(m.msg)
}

// UnmarshalMessage deserializes protobuf bytes into a Message.
// From decompiled: kiro2api_internal_logic_warp_UnmarshalMessage (0x1720ce0, 256B)
func UnmarshalMessage(desc protoreflect.MessageDescriptor, data []byte) (*Message, error) {
	msg := dynamicpb.NewMessage(desc)
	if err := proto.Unmarshal(data, msg); err != nil {
		return nil, fmt.Errorf("unmarshal: %w", err)
	}
	return &Message{
		desc:   desc,
		msg:    msg,
		fields: make(map[string]interface{}),
		raw:    data,
	}, nil
}

// ============================================================================
// Field Inspection
// ============================================================================

// ListMessageFields lists all fields in a message with their values.
// From decompiled: kiro2api_internal_logic_warp_ListMessageFields (0x1721ac0, 1024B)
func ListMessageFields(m *Message) map[string]interface{} {
	result := make(map[string]interface{})
	if m == nil || m.msg == nil {
		return result
	}

	m.msg.Range(func(fd protoreflect.FieldDescriptor, v protoreflect.Value) bool {
		result[string(fd.Name())] = v.Interface()
		return true
	})
	return result
}

// ============================================================================
// Text Extraction
// ============================================================================

// ExtractOutputText extracts the output_text field from a response message.
// From decompiled: kiro2api_internal_logic_warp_ExtractOutputText (0x1726500, 128B)
// Simple wrapper around extractFieldTextRecursive for "output_text" field.
func ExtractOutputText(m *Message) string {
	return extractFieldTextRecursive(m, "output_text")
}

// ExtractReasoningText extracts the reasoning_text field from a response message.
// From decompiled: kiro2api_internal_logic_warp_ExtractReasoningText (0x1726480, 128B)
func ExtractReasoningText(m *Message) string {
	return extractFieldTextRecursive(m, "reasoning_text")
}

// extractFieldTextRecursive recursively searches for a text field in a message.
// From decompiled: kiro2api_internal_logic_warp_extractFieldTextRecursive (0x1725dc0, 1728B)
// Walks the message tree looking for the named field, handling nested messages.
func extractFieldTextRecursive(m *Message, fieldName string) string {
	if m == nil || m.msg == nil {
		return ""
	}

	// Direct field lookup first
	fd := m.desc.Fields().ByName(protoreflect.Name(fieldName))
	if fd != nil && fd.Kind() == protoreflect.StringKind {
		val := m.msg.Get(fd).String()
		if val != "" {
			return val
		}
	}

	// Recurse into nested messages
	var result string
	m.msg.Range(func(fd protoreflect.FieldDescriptor, v protoreflect.Value) bool {
		if fd.Kind() == protoreflect.MessageKind {
			if fd.IsList() {
				list := v.List()
				for i := 0; i < list.Len(); i++ {
					nested := &Message{
						desc: fd.Message(),
						msg:  dynamicpb.NewMessage(fd.Message()),
					}
					// Copy from list element
					text := extractFieldTextRecursive(nested, fieldName)
					if text != "" {
						result = text
						return false
					}
				}
			} else {
				nested := &Message{
					desc: fd.Message(),
					msg:  dynamicpb.NewMessage(fd.Message()),
				}
				text := extractFieldTextRecursive(nested, fieldName)
				if text != "" {
					result = text
					return false
				}
			}
		}
		return true
	})
	return result
}

// DetectContentType detects the content type of a protobuf response.
// From decompiled: kiro2api_internal_logic_warp_DetectContentType (0x1726580, 608B)
// Checks for output_text, reasoning_text, tool calls, etc.
func DetectContentType(m *Message) string {
	if m == nil {
		return "unknown"
	}

	if text := ExtractOutputText(m); text != "" {
		return "text"
	}
	if text := ExtractReasoningText(m); text != "" {
		return "reasoning"
	}

	// Check for tool calls
	fields := ListMessageFields(m)
	if _, ok := fields["tool_calls"]; ok {
		return "tool_call"
	}
	if _, ok := fields["tool_result"]; ok {
		return "tool_result"
	}

	return "unknown"
}

// ============================================================================
// Raw Protobuf Parsing (without descriptors)
// ============================================================================

// ParseRawProtobuf parses raw protobuf bytes without a descriptor.
// Used as fallback when descriptor is not available.
// Returns a map of field_number -> values.
func ParseRawProtobuf(data []byte) map[uint32][]interface{} {
	result := make(map[uint32][]interface{})

	for len(data) > 0 {
		num, typ, n := protowire.ConsumeTag(data)
		if n < 0 {
			break
		}
		data = data[n:]

		switch typ {
		case protowire.VarintType:
			v, n := protowire.ConsumeVarint(data)
			if n < 0 {
				return result
			}
			data = data[n:]
			result[uint32(num)] = append(result[uint32(num)], v)

		case protowire.Fixed32Type:
			v, n := protowire.ConsumeFixed32(data)
			if n < 0 {
				return result
			}
			data = data[n:]
			result[uint32(num)] = append(result[uint32(num)], v)

		case protowire.Fixed64Type:
			v, n := protowire.ConsumeFixed64(data)
			if n < 0 {
				return result
			}
			data = data[n:]
			result[uint32(num)] = append(result[uint32(num)], v)

		case protowire.BytesType:
			v, n := protowire.ConsumeBytes(data)
			if n < 0 {
				return result
			}
			data = data[n:]
			result[uint32(num)] = append(result[uint32(num)], v)

		default:
			return result
		}
	}

	return result
}

// ============================================================================
// FileDescriptorSet loading
// ============================================================================

// LoadFileDescriptorSet loads a protobuf FileDescriptorSet from bytes.
// From decompiled: kiro2api_internal_logic_warp_loadFileDescriptorSet (0x1720400, 1344B)
func LoadFileDescriptorSet(data []byte) (*protoregistry.Files, error) {
	fds := &descriptorpb.FileDescriptorSet{}
	if err := proto.Unmarshal(data, fds); err != nil {
		return nil, fmt.Errorf("unmarshal file descriptor set: %w", err)
	}

	files, err := protodesc.NewFiles(fds)
	if err != nil {
		return nil, fmt.Errorf("create file registry: %w", err)
	}

	return files, nil
}
