# Discord Rich Presence Client

A simple client to update your **Discord Rich Presence** using Discord's IPC Pipe. This program sends customized information such as **current game**, **level**, **images**, and **interactive buttons** directly to the user's Discord profile for an immersive experience during gameplay.

## Features

- **Discord Integration**: Automatically updates your presence on Discord with custom details.
- **Interactive Buttons**: Add buttons for external links or invite others to play with you.
- **Custom Images**: Set custom game images for better visibility of the game you're currently playing.
- **Automatic Updates**: The activity is updated every 15 seconds, keeping your presence active.

## How to Use

1. **Create a Discord App**: Get your `CLIENT_ID` by creating an application on the [Discord Developer Portal](https://discord.com/developers/applications).
2. **Edit the Code**: Replace the `CLIENT_ID` value with the one you obtained.
3. **Run the Program**: Once executed, the client will automatically connect to the Discord process and update your activity.

**Important Disclaimer**  
Before doing anything, run the following command in PowerShell:

```powershell
Get-ChildItem -Path \\.\pipe\ | Where-Object { $_.Name -like "discord-ipc-*" }
