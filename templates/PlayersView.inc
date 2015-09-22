
<body>
	<?php getView("HeaderView.inc", $obj);?>
	<div id="feed">
	<table class="table_dark">
			<tr>
			    <th>Место</th>
	    		<th>Ник</th>
			    <th>Команда</th>
	    	</tr>
		<?php
		foreach ($obj as $player)
		{
    			echo "<td>1</td><td>".$player['Name']."</td><td>qwerty</td>";
		}
	?>
	</table>
	
	</div>
	<?php getView("FooterView.inc", $obj);?>
</body>
</html>

