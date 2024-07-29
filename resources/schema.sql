CREATE TABLE IF NOT EXISTS user_info (
     user_id TEXT PRIMARY KEY,
     user_number TEXT UNIQUE,
     display_name TEXT,
     registered_at INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS app_settings (
    notification_token TEXT,
    platform TEXT,
    platform_version TEXT
);