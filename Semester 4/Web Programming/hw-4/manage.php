<?php
require_once 'db.php';

$res = $conn->query("SELECT id, author, name, type FROM recipes ORDER BY id DESC");
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Manage Recipes</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="container">
    <h2>Manage Recipes</h2>
    <p><a href="index.php">Home</a> <a href="add.php">Add New</a></p>

    <table>
        <tr><th>Name</th><th>Author</th><th>Type</th><th>Actions</th></tr>
        <?php while ($row = $res->fetchArray(SQLITE3_ASSOC)): ?>
            <tr>
                <td><?= htmlspecialchars($row['name']) ?></td>
                <td><?= htmlspecialchars($row['author']) ?></td>
                <td><?= htmlspecialchars($row['type']) ?></td>
                <td>
                    <a href="edit.php?id=<?= (int)$row['id'] ?>">Edit</a>
                    <form method="post" action="delete.php" style="display:inline;" onsubmit  ="return confirm('Delete this recipe?');">
                        <input type="hidden" name="id" value="<?= (int)$row['id'] ?>">
                        <button type="submit">Delete</button>
                    </form>
                </td>
            </tr>
        <?php endwhile; ?>
    </table>
</div>
</body>
</html>
