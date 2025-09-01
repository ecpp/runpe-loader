# Loader Frontend

A modern Windows application loader with a sleek GUI interface and secure authentication system.

## 🚀 What is this?

This is a loader application that helps manage and execute Windows programs securely. It features a beautiful user interface, automatic updates, and hardware-based licensing to protect your software.

## ✨ Features

- **Modern GUI Interface** - Clean and responsive interface built with ImGui
- **Secure Authentication** - Login system with hardware ID protection
- **Auto-Updates** - Automatically checks for and downloads updates
- **License Management** - Support for product keys and subscription management
- **Dependency Management** - Automatically installs required libraries
- **In-Memory Execution** - Advanced execution without temporary files

## 📋 Requirements

- Windows 10/11 (64-bit)
- Administrator privileges (required for first run)
- DirectX 9 compatible graphics
- Internet connection for authentication

## 🔧 Installation

1. Download the latest release
2. Run the pre-loader as Administrator (only needed first time)
3. The pre-loader will:
   - Check for required dependencies
   - Download any missing libraries
   - Launch the main application
4. Create an account or login with existing credentials

## 🎯 How It Works

### Two-Part System

**1. Pre-Loader** 
- Small utility that runs first
- Checks if you have all required libraries (OpenSSL)
- Downloads missing components automatically
- Ensures everything is ready before launching the main app

**2. Main Loader**
- The actual application with the user interface
- Handles login, product management, and execution
- Communicates securely with the backend server

## 🛠️ Technical Details

### How Does RunPE Work?

The loader uses a technique called **RunPE (Process Hollowing)** to execute programs directly in memory. Think of it like this:

1. **Creates a Container** - Makes a suspended (paused) process to act as a host
2. **Prepares the Space** - Allocates memory in the host process
3. **Loads the Program** - Writes the actual program into that memory space
4. **Switches the Code** - Updates the process to run the new program instead
5. **Starts Execution** - Resumes the process with the new code running

This approach means:
- ✅ No temporary files on disk
- ✅ Harder to detect by basic antivirus
- ✅ Protects the actual program code
- ⚠️ Requires admin privileges
- ⚠️ May trigger advanced antivirus systems

### Communication & Security

The loader communicates with a backend server for:
- **User Authentication** - Secure login with hardware fingerprinting
- **License Validation** - Checks if your subscription is active
- **Product Downloads** - Fetches the programs you're licensed for
- **Version Updates** - Ensures you're running the latest version

**Security Features:**
- 🔐 Token-based authentication
- 🖥️ Hardware ID binding (prevents sharing)
- 📅 Expiration date checking
- 🔄 Automatic version control

### Under the Hood

**Technologies Used:**
- **ImGui** - For the beautiful user interface
- **DirectX 9** - For graphics rendering
- **OpenSSL** - For secure HTTPS communication
- **C++** - Core programming language

## 🏗️ Building from Source

If you want to compile the loader yourself:

1. **Requirements:**
   - Visual Studio 2022
   - Windows SDK 10.0
   - C++ development tools

2. **Steps:**
   - Open `Loader.sln` in Visual Studio
   - Select your configuration (Debug/Release)
   - Build Solution (Ctrl+Shift+B)

## ⚠️ Important Notes

- **Antivirus Software**: Some antivirus programs may flag this loader because of the RunPE technique. This is a false positive - the technique is used for legitimate software protection.
- **Admin Rights**: Required only for the first run when installing dependencies
- **Network Connection**: Required for authentication and updates
- **64-bit Only**: This loader only works on 64-bit Windows systems

## 📁 Project Structure

```
📦 Loader-Frontend
├── 📂 Main Application
│   ├── Loader.cpp         - Main program entry
│   ├── menu.cpp           - User interface
│   ├── api.cpp            - Server communication
│   └── runpe.cpp          - Memory execution engine
│
├── 📂 pre-loader/         - Dependency installer
│
├── 📂 imgui/              - UI framework files
├── 📂 OpenSSL-Win64/      - Encryption libraries
└── 📂 boost/              - C++ utilities
```

## 🤝 Contributing

Feel free to submit issues and enhancement requests!

## 📜 License

This project is for educational and legitimate software protection purposes only.

## 🔍 Troubleshooting

**Problem: Antivirus blocks the loader**
- Add an exception for the loader in your antivirus settings
- This is a false positive due to the RunPE technique

**Problem: "Please run as admin" error**
- Right-click the pre-loader and select "Run as Administrator"
- Only needed for the first run

**Problem: Connection failed**
- Check your internet connection
- Ensure firewall isn't blocking the application
- Server might be under maintenance

## 📞 Support

For issues or questions, please open an issue on GitHub.

---

*Built with ❤️ for secure software distribution*