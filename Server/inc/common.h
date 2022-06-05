#pragma once

enum GameMessage {
    // Test (remove later)
    Send,

    // Client sending
    ON_KEY_PRESSED,
    CLIENT_DISCONNECTED,

    // Server sending
    NEW_GAME_STATE,
    NEW_GAME_MAP,
    SERVER_STOP,
    CLIENT_CONNECTED
};