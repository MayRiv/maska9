<html>
<head>
	<link rel="stylesheet" type="text/css" href="maska9.css"/>
</head>
<body>
	<?php getView("HeaderView.inc", $obj);?>
	<div>
		<form action="auth.php" method="post">
  			<p><input type="text" name="Name"></p>
			<p><input type="text" name="Pass"></p>
  			<p><input type="submit" value="Authorize"></p>
 		</form>
	</div>
	<?php getView("FooterView.inc", $obj);?>
</body>
</html>
