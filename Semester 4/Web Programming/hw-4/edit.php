<?php
require_once 'db.php';

$id = (int)$_GET['id'];

$error = '';

$stmt = $conn->prepare("SELECT author, name, type, recipe FROM recipes WHERE id = :id");
$stmt->bindValue(':id', $id, SQLITE3_INTEGER);
$res = $stmt->execute();
$item = $res ? $res->fetchArray(SQLITE3_ASSOC) : false;

if (!$item) {
    header('Location: manage.php');
    exit;
}

$author = trim($_POST['author'] ?? $item['author']);
$name = trim($_POST['name'] ?? $item['name']);
$type = trim($_POST['type'] ?? $item['type']);
$recipe = trim($_POST['recipe'] ?? $item['recipe']);

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if ($author === '' || $name === '' || $type === '' || $recipe === '') {
        $error = 'All fields are required.';
    } elseif (strlen($author) < 2) {
        $error = 'Author must be at least 2 characters.';
    } elseif (strlen($name) < 3) {
        $error = 'Name must be at least 3 characters.';
    } elseif (strlen($type) < 3) {
        $error = 'Type must be at least 3 characters.';
    } elseif (strlen($recipe) < 10) {
        $error = 'Recipe must be at least 10 characters.';
    } else {
        $stmt = $conn->prepare("UPDATE recipes SET author = :author, name = :name, type = :type, recipe = :recipe WHERE id = :id");
        $stmt->bindValue(':author', $author, SQLITE3_TEXT);
        $stmt->bindValue(':name', $name, SQLITE3_TEXT);
        $stmt->bindValue(':type', $type, SQLITE3_TEXT);
        $stmt->bindValue(':recipe', $recipe, SQLITE3_TEXT);
        $stmt->bindValue(':id', $id, SQLITE3_INTEGER);
        if ($stmt->execute() !== false) {
            header('Location: manage.php');
            exit;
        } else {
            $error = 'Update failed.';
        }
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Edit Recipe</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="container">
    <h2>Edit Recipe</h2>
    <p><a href="manage.php">Back to Manage</a></p>

    <?php if ($error): ?><p class="error"><?= htmlspecialchars($error) ?></p><?php endif; ?>

    <form method="post">
        <input type="hidden" name="id" value="<?= $id ?>">

        <div class="row">
            <label>Author</label>
            <input type="text" name="author" value="<?= htmlspecialchars($author) ?>" >
        </div>

        <div class="row">
            <label>Name</label>
            <input type="text" name="name" value="<?= htmlspecialchars($name) ?>" >
        </div>

        <div class="row">
            <label>Type</label>
            <input type="text" name="type" value="<?= htmlspecialchars($type) ?>" >
        </div>

        <div class="row">
            <label>Recipe</label>
            <textarea name="recipe" rows="6" ><?= htmlspecialchars($recipe) ?></textarea>
        </div>

        <div class="actions">
            <button type="submit">Save</button>
            <a href="manage.php" onclick="return confirm('Cancel editing?')">Cancel</a>
        </div>
    </form>
</div>
</body>
</html>
