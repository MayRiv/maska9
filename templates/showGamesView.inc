<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
<?php
	if (isset($obj))
	{
		foreach ($obj as $roundNumber => $tables) {
			echo "<tr><td colspan='2'>$roundNumber раунд</td></tr>";
			foreach ($tables as $roomId => $game) {
				echo "<tr><td>$roomId зал</td><td>Ведущий $game[0]</td><td>Победила команда $game[1]</td><td><a href='/maska9/?action=showGames&gameid=$game[2]'>Подробно</a></td><td><a href='/?action=showGames&gameid=$game[2]&delete=1'>Удалить</a></td></tr>";
			}
		}
	}
?>
	</table>
<?php getView("Footer.inc", $obj);?>

</body>