#!/bin/bash
# ------------------------------------------------------------
# GeoLocator Automated Test Script
# Author: Brian Lorick
# Date: 11/04/2025
# Description:
#   Runs multiple valid and invalid IP address test cases
#   through the GeoLocator program, saving outputs to logs.
# ------------------------------------------------------------

# Define paths
PROGRAM="./build/GeoLocator"     # compiled program binary
IP_LIST="./data/example_ips.txt" # list of IPs to test
OUTPUT_DIR="./tests/results"     # directory for logs
REFERENCE_FILE="./tests/run_test_data.txt"

# Create results directory if not exists
mkdir -p "$OUTPUT_DIR"

# Check if program exists
if [ ! -f "$PROGRAM" ]; then
  echo "❌ Error: Compiled program not found at $PROGRAM"
  echo "Please run: make"
  exit 1
fi

# Check if IP list exists
if [ ! -f "$IP_LIST" ]; then
  echo "❌ Error: IP list not found at $IP_LIST"
  exit 1
fi

echo "========================================="
echo " GeoLocator Automated Test Execution"
echo "========================================="

# Read each IP from the data file and run the program
while IFS= read -r ip; do
  # Skip comments and empty lines
  if [[ "$ip" == \#* || -z "$ip" ]]; then
    continue
  fi

  echo "▶️  Testing IP: $ip"

  # Replace illegal characters in filename (colons, slashes)
  safe_ip="${ip//[:\/]/_}"

  # Run test and capture output
  "$PROGRAM" <<< "$ip" > "$OUTPUT_DIR/${safe_ip}.log" 2>&1

  # Check return code
  if [ $? -eq 0 ]; then
    echo "✅ Completed: $ip → results/${safe_ip}.log"
  else
    echo "⚠️  Error detected for $ip → results/${safe_ip}.log"
  fi

  echo "-----------------------------------------"

done < "$IP_LIST"

echo "All tests complete."
echo "Results stored in: $OUTPUT_DIR"
