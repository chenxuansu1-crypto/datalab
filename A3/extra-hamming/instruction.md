# Extended Hamming Code (16,11) — 50 Points

In this assignment, you will implement error detection and correction using the **Extended Hamming (16,11) code**. This code encodes 11 data bits into a 16-bit word using Hamming error correction with an additional overall parity bit.

**Structure:**
- **Positions 1–15:** Standard Hamming (15,11) code with parity bits at positions 1, 2, 4, and 8
- **Position 16:** Overall parity bit (XOR of positions 1–15) for enhanced error detection

This extra parity bit enables detection (but not correction) of two-bit errors while still allowing single-bit errors to be corrected.

---

## Handout Instructions

- Find `hamming16.c` in your GitHub Classroom repository
- Implement the three functions described below
- Commit and push your changes back to GitHub Classroom

**Study Resources (Highly Recommended):**
- **Video tutorial:** <https://youtu.be/X8jsijhllIA?si=YNJvFX5miCej71eJ>
- **Interactive simulator:** <https://harryli0088.github.io/hamming-code/>
  - Create your own test cases and verify them manually with this simulator!

---

## Implementation Constraints

- **Operators:** Use only bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`) for all bit manipulations
- **Loops & Conditionals:** May be used in the decoding function (e.g., when computing the syndrome)
- **Documentation:** Comment your code clearly—explain bit ordering, parity calculations, and syndrome correction

---

## Important: Bit Indexing Convention

**All position numbers in this assignment use 1-indexing:**

| 1-Indexed Position | Bit Index in C | How to Access in Code |
|---|---|---|
| Position 1 (LSB) | Index 0 | `(code >> 0) & 1` |
| Position 2 | Index 1 | `(code >> 1) & 1` |
| Position 7 | Index 6 | `(code >> 6) & 1` |
| Position 16 (MSB) | Index 15 | `(code >> 15) & 1` |

**Key Rule:** To convert position number to bit index, subtract 1.  
**Example:** Position 7 → use bit index 6 in your code

---

## Part 1: Extended Hamming Encoding

**Function Prototype:**
```
uint16_t extendedHammingEncode(uint16_t data);
```
**Input:** 
- The lower 11 bits of `data` (values 0–2047)

**Output:** 
- A 16-bit code word where:
  - Positions 1–15 form the Hamming (15,11) code
  - Position 16 is the overall parity (XOR of positions 1–15)

**Data Bit Placement:**
The 11 data bits occupy positions: 3, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15  
Parity bits occupy positions: 1, 2, 4, 8

---

## Part 2: Extended Hamming Decoding

**Function Prototype:**
```
uint16_t extendedHammingDecode(uint16_t code, int *errorPos);
```
**Input:**
- `code`: A 16-bit Extended Hamming code word (possibly containing errors)

**Output:**
- Returns the original 11-bit data (in the lower 11 bits)

**Error Detection & Correction Algorithm:**

1. **Compute syndrome:** Recompute parity bits for positions 1, 2, 4, 8
2. **Compute overall parity:** XOR all bits at positions 1–15
3. **Compare with stored overall parity** at position 16
4. **Determine error type:**

| Syndrome | Overall Parity Match? | Error Type | Action |
|---|---|---|---|
| 0 | Yes | No error | Set `*errorPos = 0` |
| 0 | No | Error at position 16 | Set `*errorPos = 16`, correct bit 16 |
| Non-zero | No | Single-bit error | Set `*errorPos = syndrome`, correct that bit |
| Non-zero | Yes | Double-bit error | Set `*errorPos = -1` (uncorrectable) |

**Set `*errorPos` to:**
- `0` if no error detected
- `1` to `16` if single-bit error corrected (1-indexed position)
- `-1` if uncorrectable error detected

---

## Part 3: Error Injection

**Function Prototype:**
```
uint16_t introduceError(uint16_t code, int bitPos);
```
**Input:**
- `code`: A 16-bit code word
- `bitPos`: Position from 1 to 16 (1-indexed) to flip

**Output:**
- Code word with the specified bit flipped

**Purpose:** Simulate transmission errors for testing

**Implementation:**
return code ^ (1 << (bitPos - 1));
---

## Running Your Program

- Test without errors: `./hamming16 0x3A5`
- Test with error at position 7: `./hamming16 0x3A5 7`
- Test with error at position 16 (overall parity bit): `./hamming16 0x3A5 16`

**Expected behavior:**
- Without errors: Should decode correctly
- With single-bit error: Should detect, correct, and report position
- With double-bit errors: Should detect as uncorrectable

---

## Tips for Success

1. **Start with encoding:** Get the data placement and parity calculation working first
2. **Test incrementally:** Use the online simulator to verify your encoding logic
3. **Pay attention to indexing:** Remember to subtract 1 when converting positions to bit indices
4. **Test all error cases:** No error, single error in data bit, single error in parity bit, error in position 16, and double errors
5. **Comment your code:** Explain which positions you're checking and why