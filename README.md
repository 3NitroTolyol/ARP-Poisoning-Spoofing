# ARP-Poisoning-Spoofing

# Low-Level C ARP Spoofer (MITM Demonstration)

A lightweight, high-performance network security tool written in **pure C** utilizing the **Npcap SDK**. This project demonstrates the mechanics of Address Resolution Protocol (ARP) cache poisoning, establishing a Man-in-the-Middle (MITM) position between a target host (victim) and the local gateway (router).

## ⚠️ Ethical Disclaimer & Purpose
This repository is created strictly for **educational, research, and ethical hacking purposes**. It was developed as part of a University Cybersecurity curriculum to practicalize knowledge of network protocols and low-level packet injection. 
* Do **NOT** run this tool on networks where you do not have explicit, written authorization.
* The author assumes no liability for any misuse, damage, or illegal activities caused by this software.

## 🛠️ Technical Features
* **Byte-Aligned Structs:** Manual compilation of Ethernet and ARP headers using `#pragma pack(push, 1)` for precise network delivery.
* **Dynamic Interface Discovery:** Automatically scans Windows network adapters, identifies available interfaces, and enforces `DLT_EN10MB` (Ethernet/Wi-Fi link layer) validation.
* **Robust Input Sanitization:** Cross-platform input handling utilizing a custom `getchar()` buffer flush mechanism to prevent string clipping and token skipping during target configuration.
* **Aggressive Injection Loop:** Implements a stable transmission sequence (1 packet/sec) to continuously overwrite target ARP tables and maintain MITM persistence against router updates.

## 📋 Prerequisites
To build and execute this project on Windows, ensure you have:
1. **MinGW-w64 (GCC):** Added to your system Environment Variables (`PATH`).
2. **Npcap Driver:** Installed on your machine with the **"API-compatible with WinPcap"** option checked.
3. **Npcap SDK (v1.16):** Downloaded and extracted. By default, the automated build script expects the `npcap-sdk-1.16` folder to be located one level above this project folder (`../npcap-sdk-1.16`).

## 🚀 How to Build and Run

1. Clone the Repository
```bash
git clone https://github.com/3NitroTolyol/ARP-Poisoning-Spoofing.git
cd ARP-Poisoning-Spoofing

2. Compilation
build.bat
Or compile manually via your terminal using GCC:
gcc ARP.c -o ARP.exe -I ../npcap-sdk-1.16/Include -L ../npcap-sdk-1.16/Lib/x64 -lwpcap -lws2_32

3. Execution (Requires Administrator Privileges)
Low-level raw packet injection requires root privileges on Windows.

Open Windows Command Prompt (cmd) or PowerShell as Administrator.

Navigate to your folder and run the executable:
ARP.exe

🔍 How to Verify (Wireshark Configuration)

Launch Wireshark on your host machine and select your active Wi-Fi/Ethernet interface.

In the display filter bar, use the following filters to analyze your tool's performance:

arp — To watch your generated ARP Reply packets flood the network every second.

arp.duplicate-address-detected — Wireshark will trigger a dark-colored warning confirming that your machine's MAC is successfully impersonating the router's IP.

ip.addr == VICTIM_IP — (After enabling IP Forwarding) To capture all routed transit traffic passing from the victim's phone/PC through your machine.