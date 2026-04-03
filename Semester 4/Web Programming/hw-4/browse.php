<?php
require_once 'db.php';

$types = [];
$r = $conn->query("SELECT DISTINCT type FROM recipes ORDER BY type");
if ($r) {
    while ($row = $r->fetchArray(SQLITE3_ASSOC)) {
        $types[] = $row['type'];
    }
}
?>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Browse Recipes</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="container">
    <h2>Browse Recipes</h2>
    <p><a href="index.php">Home</a></p>

    <div class="row">
        <label >Recipe type:</label>
        <select id="type">
            <option value="">All</option>
            <?php foreach ($types as $t): ?>
                <option ><?= htmlspecialchars($t) ?></option>
            <?php endforeach; ?>
        </select>
    </div>

    <div class="actions">
        <button onclick="loadRecipes()">Load</button>
    </div>

    <p>Previous filter: <span id="prevFilter">none</span></p>

    <div id="recipesBox"></div>
</div>

<script>
function loadRecipes() {
    const type = document.getElementById('type').value;
    document.getElementById('prevFilter').innerText = type === '' ? 'All' : type;

    fetch('ajax_recipes.php?type=' + encodeURIComponent(type))
        .then(r => r.text())
        .then(html => {
            document.getElementById('recipesBox').innerHTML = html;
        });
}

window.onload = function () {
    loadRecipes();
};
</script>
</body>
</html>
