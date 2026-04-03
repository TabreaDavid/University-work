<?php
require_once 'db.php';

$type = trim($_GET['type']) ?? '';

$stmt = $conn->prepare("SELECT id, author, name, type, recipe FROM recipes WHERE (:type = '' OR type = :type) ORDER BY id DESC");
$stmt->bindValue(':type', $type, SQLITE3_TEXT);

$res = $stmt->execute();

echo '<table>';
echo '<tr><th>Name</th><th>Author</th><th>Type</th><th>Recipe</th></tr>';
while ($row = $res->fetchArray(SQLITE3_ASSOC)) {
    echo '<tr>';
    echo '<td>' . htmlspecialchars($row['name']) . '</td>';
    echo '<td>' . htmlspecialchars($row['author']) . '</td>';
    echo '<td>' . htmlspecialchars($row['type']) . '</td>';
    echo '<td>' . htmlspecialchars($row['recipe']) . '</td>';
    echo '</tr>';
}
echo '</table>';
