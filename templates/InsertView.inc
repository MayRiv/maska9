<div id="inserter">
<?=$obj['id'];?>
<form action="/maska9/?action=insertGame" method="post">
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="text" name=Player[] list="players_list"></p>
	<p><input type="submit" value="Send"></p>
</form>
<datalist id="players_list">
<?php	foreach ($obj['players'] as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
</div>
