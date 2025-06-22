# Game-development

# 🎮 FPS JSON Box Shooter

## 📌 Overview

This is a **First Person Shooter game** developed in **Unreal Engine C++**, which dynamically fetches JSON data online to spawn interactive colored boxes.

- ✅ **Boxes have custom colors, health, and scores**
- ✅ **Player shoots to damage and destroy boxes**
- ✅ **Each destroyed box awards points**
- ✅ **Player’s score is displayed with a UUserWidget**
- ✅ **Uses only Unreal's native C++ API — no plugins**

---

## ⚙️ Features

- Online JSON download using Unreal’s HTTP module
- JSON parsing with error handling
- Dynamic spawning of static mesh boxes based on JSON data:
  - Type
  - Color (applied using dynamic material)
  - Health
  - Score
  - Transform (position, rotation, scale)
- Basic shooting with line trace
- Health system: each hit reduces health by 1
- Box destroyed at zero health, player gains score
- Live score shown with a C++ UUserWidget

---

## 📁 Folder Structure

