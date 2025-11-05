# 🌍 IPGeoLoc — IP Address Geolocation Lookup (C Language)

**Author:** Brian Lorick  
**Date:** November 2025  
**Version:** 1.0  
**Language:** C  
**License:** MIT  

---

## 🧭 Overview

**IPGeoLoc** is a command-line C program that retrieves **geolocation data for a given IP address** using the [ipinfo.io](https://ipinfo.io) public API.  
It demonstrates practical API integration, JSON parsing, and system command usage within a C environment — all while maintaining strong input validation and error handling.

The program is lightweight, modular, and designed for educational and practical use in networking, cybersecurity, and system scripting.

---

## 🚀 Features

- Lookup by **IPv4** and **IPv6** addresses  
- Retrieves:
  - City  
  - Region / State  
  - Country  
  - Organization (ISP)  
  - Coordinates (Latitude, Longitude)
- Uses `curl` for HTTP requests (no external libraries required)
- Handles invalid and private IPs gracefully
- Auto-deletes temporary files after lookup
- Fully tested with automated and manual test suites

---

## 🧩 File & Directory Structure

```
IPGeoLoc/
├── src/
│   └── IPGeoLoc.c                ← full program source code (C)
│
├── data/
│   ├── example_ips.txt           ← main test dataset (valid & invalid IPs)
│   ├── ip_batch_list.txt         ← sample for future batch lookups
│   ├── malformed_ips.txt         ← malformed inputs for validation testing
│   └── README.md                 ← documentation for dataset usage
│
├── tests/
│   ├── run_tests.sh              ← automated test runner script
│   ├── run_test_data.txt         ← expected results reference
│   ├── test_cases.txt            ← organized list of test inputs
│   ├── test_notes.txt            ← developer notes & manual testing tips
│   └── results/                  ← folder where logs are saved
│
├── docs/
│   ├── DESIGN.md                 ← design breakdown and functional flow
│   └── API_REFERENCE.md          ← API endpoint and data field details
│
├── build/                        ← output directory for compiled binaries
│
├── Makefile                      ← simple GCC build automation
├── .gitignore                    ← ignores build files, binaries, temp data
├── LICENSE                       ← MIT open-source license
└── README.md                     ← this file
```

---

## 🧪 Using OnlineGDB

1. Upload or paste the contents of `src/IPGeoLoc.c`  
2. Choose **Language:** C  
3. Click **Run**  
4. Enter an IP address when prompted (e.g., `8.8.8.8`)

---

## 💡 Example Output

```
=== IPGeoLoc (IP Address Lookup) ===

Enter an IP address (e.g., 8.8.8.8): 8.8.8.8

=== IPGeoLoc Results ===
City: Mountain View
Region: California
Country: United States
Organization: AS15169 Google LLC
Coordinates: 37.4056,-122.0775

Lookup complete.
```

---

## 🧪 Testing

### Automated Tests

The script `tests/run_tests.sh` executes all IPs listed in `/data/example_ips.txt`, logs outputs, and verifies expected behavior.

```bash
chmod +x tests/run_tests.sh
./tests/run_tests.sh
```

or via Makefile:

```bash
make test
```

Results are saved under:
```
tests/results/
```

### Manual Tests

You can also run IPGeoLoc manually with user input for single IPs.

---

## 🧱 Design Summary

**Core Logic (src/IPGeoLoc.c)**  
- Prompts user for IP input  
- Constructs API URL: `https://ipinfo.io/<IP>/json`  
- Fetches data via `curl` command  
- Parses output manually from JSON text  
- Handles and reports network or parsing errors  
- Deletes temporary file `geo_temp.json`

---

## 🧰 Dependencies

- **C Standard Library:** `stdio.h`, `stdlib.h`, `string.h`  
- **System Utility:** `curl` (must be installed on host system)

Check if curl exists:
```bash
curl --version
```

---

## ⚠️ Error Handling

| Condition | Message |
|------------|----------|
| No input provided | `Error: Invalid IP address input.` |
| Invalid IP format | `Error: Invalid or unreachable IP address.` |
| Network or curl failure | `Error: Failed to retrieve data. Please check your internet connection.` |
| Empty API response | `Error: No valid data returned. The IP may be unreachable or invalid.` |

---

## 🧪 Quality Assurance

The `tests/` directory includes:

- ✅ Automated batch tests  
- 🧠 Manual test notes  
- 🧩 Expected result references  
- 📊 Organized result logs  

All test files are fully documented to ensure repeatable results across systems.

---

## 🧭 Future Enhancements

- Replace `system("curl")` with `libcurl` or `WinHTTP` integration  
- Add JSON parsing via `cJSON` or `jansson`  
- Implement file-based batch lookup mode  
- Export results as CSV or JSON  
- Add network timeout and retry logic  
- GUI or web-based interface version  

---

## 📜 License

This project is licensed under the **MIT License**.  
See [LICENSE](LICENSE) for full details.

---

## 👤 Author

**Brian Lorick**  
📅 *Developed October–November 2025*  
💬 *For educational and open-source community use.*

---

## 🧠 Summary

**IPGeoLoc** is a complete, portable example of integrating web APIs with native C programs — emphasizing reliability, maintainability, and clarity of design.  
It includes structured documentation, automated testing, and clean modular organization to demonstrate real-world project best practices.

---

© 2025 **Brian Lorick** — *IPGeoLoc Project*








