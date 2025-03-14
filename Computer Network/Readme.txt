# Turbocloakvpn Project

This project includes a Python Flask backend application and a Flutter mobile VPN application. The VPN infrastructure uses OpenVPN.

## Contents
- [Requirements](#requirements)
- [Setup](#setup)
- [Python Flask Application](#python-flask-application)
  - [Installation and Running](#installation-and-running)
- [Flutter Mobile Application](#flutter-mobile-application)
  - [Installation and Running](#installation-and-running)
- [VPN Configuration](#vpn-configuration)
  - [OpenVPN Setup](#openvpn-setup)

## Requirements

- Python 3.x
- Flask
- Gunicorn
- Flutter SDK
- OpenVPN

## Setup

### Python Flask Application

#### Installation and Running

1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd <repository_directory>
Install the required Python packages:


pip install -r requirements.txt
Start the Flask application:

gunicorn -w 4 -b 0.0.0.0:8000 main:app
Flutter Mobile Application
Installation and Running
Install the Flutter SDK. Visit Flutter Installation for instructions.

Clone the repository:

git clone <repository_url>
cd <repository_directory>/flutter_app
Install the required dependencies:


flutter pub get
Run the application:

flutter run


Create or modify OpenVPN configuration files. Below is an example configuration file:

client
dev tun
proto udp
remote <server_ip> <port>
resolv-retry infinite
nobind
persist-key
persist-tun
ca ca.crt
cert client.crt
key client.key
remote-cert-tls server
cipher AES-256-CBC
verb 3
Start the OpenVPN service:





License
This project is licensed under the MIT License. See the LICENSE file for more details.


