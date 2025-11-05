# 🧱 IPGeoLoc — Program Design & Architecture

**Author:** Brian Lorick  
**Date:** November 2025  
**Version:** 1.0  
**Language:** C  

---

## 📘 Overview

**IPGeoLoc** is a single-file C program that performs **IP address geolocation lookups** using the public API provided by [ipinfo.io](https://ipinfo.io).  
This document outlines the program’s design, functional flow, data handling, and control logic.

The program was engineered for clarity, reliability, and educational transparency — suitable for demonstrating:
- API integration via system calls (`curl`)
- JSON parsing with standard C functions
- Structured program flow and error handling
- Real-world data retrieval and validation

---

## 🧩 High-Level Architecture

```
                ┌────────────────────────────┐
                │        User Input          │
                │  (Enter IP address)        │
                └────────────┬───────────────┘
                             │
                             ▼
                ┌────────────────────────────┐
                │  URL Construction          │
                │  "https://ipinfo.io/IP/json"│
                └────────────┬───────────────┘
                             │
                             ▼
                ┌────────────────────────────┐
                │  Data Retrieval via curl   │
                │  (system("curl -s ..."))   │
                └────────────┬───────────────┘
                             │
                             ▼
                ┌────────────────────────────┐
                │  JSON File Parsing          │
                │  Extract: city, region, etc.│
                └────────────┬───────────────┘
                             │
                             ▼
                ┌────────────────────────────┐
                │  Data Validation & Errors  │
                │  (Invalid IP, no data)     │
                └────────────┬───────────────┘
                             │
                             ▼
                ┌────────────────────────────┐
                │  Output & Cleanup          │
                │  Display results, delete   │
                │  geo_temp.json             │
                └────────────────────────────┘
```

---

## ⚙️ Core Design Principles

- **Simplicity:**  
  Uses a single C source file and standard libraries only.  

- **Portability:**  
  Works on Windows, Linux, and macOS with only `curl` required.  

- **Clarity:**  
  Explicit variable naming, descriptive comments, and modular sections (INPUT, PROCESSING, OUTPUT).  

- **Safety:**  
  String handling is bounded using `snprintf`, `fgets`, and fixed-size buffers.  

- **Cleanup:**  
  Temporary files are deleted at the end of execution to prevent clutter.

---

## 🧮 Functional Sections

### 1. Input Handling
- Prompts user for an IP address.
- Validates non-empty, reasonable input.
- Rejects empty or malformed entries early.

### 2. URL and Command Construction
- Constructs API request URL dynamically:  
  `https://ipinfo.io/<IP>/json`
- Builds system command for curl:  
  `curl -s <URL> -o geo_temp.json`

### 3. API Retrieval
- Executes curl command silently (`-s` flag).
- Stores JSON response into a temporary file: `geo_temp.json`.

### 4. File Parsing
- Opens JSON file using `fopen()`.
- Reads line-by-line with `fgets()`.
- Extracts fields using `strstr()` and `sscanf()`.

### 5. Error Handling
- Detects missing fields, empty file, or error responses from the API.
- Displays clear user-friendly messages.

### 6. Output
- Displays formatted results in labeled order:
  ```
  City:
  Region:
  Country:
  Organization:
  Coordinates:
  ```
- Uses fallback `"N/A"` when a field is missing.

### 7. Cleanup
- Deletes `geo_temp.json` automatically using `remove()`.

---

## 🧠 Memory & Performance Considerations

- All variables are statically allocated with defined buffer sizes.  
- No heap memory allocation (no `malloc`/`free`).  
- Single network call per execution.  
- Lightweight footprint (~15 KB executable).  

---

## 🧰 Dependencies

| Dependency | Purpose | Platform |
|-------------|----------|-----------|
| `curl` | Fetches API data over HTTPS | All OS |
| `stdio.h` | Input/output operations | C Standard |
| `stdlib.h` | System calls and process control | C Standard |
| `string.h` | String manipulation | C Standard |

---

## 🧩 Error Handling Flow

| Error Type | Detection Method | User Feedback |
|-------------|------------------|----------------|
| Empty input | `strlen(ipAddress) < 3` | “Error: Invalid IP address input.” |
| Curl failure | Non-zero return from `system()` | “Error: Failed to retrieve data.” |
| Missing file | `fopen()` returns NULL | “Error: Could not open response file.” |
| Invalid IP / API error | Detect `"error"` in JSON | “Error: Invalid or unreachable IP address.” |
| No valid data | All fields empty | “Error: No valid data returned.” |

---

## 🧪 Testing & Validation

The **`tests/`** directory contains:
- Automated test script (`run_tests.sh`)
- Expected outputs (`run_test_data.txt`)
- IP datasets under `/data/`

Each test ensures:
- Proper error detection
- Correct formatting of valid responses
- Clean resource cleanup (`geo_temp.json` removed)

---

## 🧭 Future Design Improvements

- Replace system curl with `libcurl` for safer HTTPS requests.  
- Use `cJSON` for structured JSON parsing instead of `sscanf`.  
- Add support for batch mode and offline caching.  
- Log lookups to file for audit tracking.  
- Optional configuration file for API keys or alternate providers.

---

## 🧾 Summary

**IPGeoLoc** demonstrates best practices in:
- Procedural program flow  
- Safe string handling  
- API data integration in C  
- Reproducible testing and documentation  

Its modular structure and thorough commenting make it ideal for learning, demonstration, or extension into larger projects.

---

© 2025 **Brian Lorick** — *IPGeoLoc Project*
