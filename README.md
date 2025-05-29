## 🔐 File Encryption/Decryption System Based on 3DES, Blowfish, and MD5

### ✅ Usage Instructions

1. Select the file to be encrypted.
2. Choose the encryption mode:

   * **Single encryption**: Use either 3DES or Blowfish.
   * **Double encryption**: Use **3DES first**, followed by **Blowfish**.
3. Execute the encryption process.

Additionally, a **driver-based encryption** method is available, which can be toggled via a dedicated switch in the UI.

---

### ❗ Existing Issues

1. **3DES encryption is not compatible with Blowfish**, causing problems in double encryption scenarios.
2. **Appending the MD5 checksum at the end of the ciphertext** is not a proper or secure method.
3. When using **double encryption**, the **decryption order must be the reverse** of the encryption order.

---

### 🔧 Improvements to Be Made

1. **Key storage method** should be updated — for example, by **storing keys in a MySQL database**.
2. **Double encryption** could be **integrated into a unified encryption scheme** to simplify the process.
3. **Optimize code performance**:

   * Improve speed through **multithreading**.
   * Use **data segmentation** to enhance encryption/decryption efficiency.
