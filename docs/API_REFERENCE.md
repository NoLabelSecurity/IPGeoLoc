# 🌐 IPGeoLoc — API Reference Documentation

**Author:** Brian Lorick  
**Date:** November 2025  
**Version:** 1.0  
**API Used:** [ipinfo.io](https://ipinfo.io)

---

## 📘 Overview

The **IPGeoLoc** program uses the public API endpoint provided by **ipinfo.io** to obtain geolocation details for a user-supplied IP address.  
This document provides reference information about the API request, response format, and key fields extracted by the program.

---

## 🔗 API Endpoint

**Base URL:**
```
https://ipinfo.io/
```

**Query Format:**
```
https://ipinfo.io/<IP>/json
```

**Example:**
```
https://ipinfo.io/8.8.8.8/json
```

---

## ⚙️ HTTP Request Details

| Parameter | Description |
|------------|-------------|
| **Method** | GET |
| **Protocol** | HTTPS |
| **Response Type** | JSON |
| **Authentication** | None required (for free-tier lookups) |
| **Timeout** | Managed by system `curl` configuration |

**Example command executed by program:**
```bash
curl -s https://ipinfo.io/8.8.8.8/json -o geo_temp.json
```

---

## 🧩 Response Structure

Below is an example JSON response returned by ipinfo.io:

```json
{
  "ip": "8.8.8.8",
  "hostname": "dns.google",
  "city": "Mountain View",
  "region": "California",
  "country": "US",
  "loc": "37.4056,-122.0775",
  "org": "AS15169 Google LLC",
  "postal": "94043",
  "timezone": "America/Los_Angeles"
}
```

---

## 📋 Fields Extracted by IPGeoLoc

| JSON Key | Example Value | Description |
|-----------|----------------|-------------|
| `city` | `"Mountain View"` | City of the IP’s location |
| `region` | `"California"` | State or region name |
| `country` | `"US"` | Two-letter ISO country code |
| `org` | `"AS15169 Google LLC"` | Organization / ISP associated with the IP |
| `loc` | `"37.4056,-122.0775"` | Latitude and longitude coordinates |

The program intentionally ignores other fields (e.g., `postal`, `timezone`, `hostname`) to keep output concise and human-readable.

---

## 🧠 Error Responses

When the API cannot process the IP or when the IP is invalid/unroutable, ipinfo.io returns:

```json
{
  "error": {
    "title": "Wrong ip",
    "message": "Please provide a valid IP address"
  }
}
```

In such cases, **IPGeoLoc** detects the `"error"` key and prints:

```
Error: Invalid or unreachable IP address.
```

---

## 🧮 API Usage Limits

| Tier | Requests per Day | Notes |
|------|------------------|-------|
| Free | ~50,000 | No API key required |
| Paid | Unlimited | Requires registration |

For educational or small-scale use, the free tier is more than sufficient.

---

## 🧰 Integration Notes

- The program uses the command-line utility `curl`, not a library.  
- Responses are written to a temporary JSON file for parsing.  
- The use of `-s` (silent) suppresses progress messages for clean console output.  
- API latency typically under 200ms per request.  

---

## 🧭 Future API Enhancements

- Switch to **libcurl** for embedded HTTPS calls.  
- Allow users to specify a custom API endpoint via CLI argument.  
- Support alternate geolocation APIs (e.g., ip-api.com, ipstack.com).  
- Extend parsing to include timezone and postal code.  
- Add offline lookup cache file for repeated IPs.

---

## 🧾 Summary

**IPGeoLoc** integrates seamlessly with ipinfo.io’s REST API, providing lightweight, reliable IP geolocation with no dependencies beyond `curl` and the C standard library.  
It uses simple text parsing to convert live JSON data into readable console output — ideal for learners and lightweight applications alike.

---

© 2025 **Brian Lorick** — *IPGeoLoc Project*
