<html>
<head>
	<link rel="stylesheet" type="text/css" href="maska9.css"/>
</head>
<body>
	<?php getView("HeaderView.inc", $obj);?>
	<div id="feed">
	<?php
	foreach ($obj as $player)
    		echo $player['Name'];
	?>
	</div>
	<?php getView("FooterView.inc", $obj);?>
</body>
</html>

