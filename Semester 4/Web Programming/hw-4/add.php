<?php
require_once 'db.php';

$error = '';

$author = trim($_POST['author'] ?? '');
$name = trim($_POST['name'] ?? '');
$type = trim($_POST['type'] ?? '');
$recipe = trim($_POST['recipe'] ?? '');

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
        $error = 'Recipe must be at least 10 characters .';
    } else {
        $stmt = $conn->prepare("INSERT INTO recipes(author, name, type, recipe) VALUES(:author, :name, :type, :recipe)");
        $stmt->bindValue(':author', $author, SQLITE3_TEXT);
        $stmt->bindValue(':name', $name, SQLITE3_TEXT);
        $stmt->bindValue(':type', $type, SQLITE3_TEXT);
        $stmt->bindValue(':recipe', $recipe, SQLITE3_TEXT);
        if ($stmt->execute() !== false) {
            header('Location: manage.php');
            exit;
        } else {
            $error = 'Insert failed.';
        }
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Add Recipe</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="container">
    <h2>Add Recipe</h2>
    <p><a href="index.php">Home</a></p>

    <?php if ($error): ?><p class="error"><?= htmlspecialchars($error) ?></p><?php endif; ?>

    <form method="post">
        <div class="row">
            <label>Author</label>
            <input type="text" name="author" value="<?= htmlspecialchars($author) ?>">
        </div>

        <div class="row">
            <label>Name</label>
            <input type="text" name="name" value="<?= htmlspecialchars($name) ?>">
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
            <button type="submit">Add</button>
            <a href="index.php" onclick="return confirm('Cancel adding recipe?')">Cancel</a>
        </div>
    </form>
</div>
</body>
</html>
