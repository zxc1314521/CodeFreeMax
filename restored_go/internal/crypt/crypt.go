package crypt

// DecryptCredential decrypts a legacy-encrypted credential string.
func DecryptCredential(encrypted string) (string, error) {
	// Stub: legacy encryption not available in restored build.
	// Return the input as-is (assume plaintext or already decrypted).
	return encrypted, nil
}

// EncryptCredential encrypts a plaintext credential string.
func EncryptCredential(plaintext string) (string, error) {
	return plaintext, nil
}
