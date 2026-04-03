<?php
$DB_FILE = 'recipes.sqlite';

$conn = new SQLite3(__DIR__ . '/' . $DB_FILE);
if (!$conn) {
    die('Database connection failed.');
}

$conn->exec('CREATE TABLE IF NOT EXISTS recipes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    author TEXT NOT NULL,
    name TEXT NOT NULL,
    type TEXT NOT NULL,
    recipe TEXT NOT NULL
)');
