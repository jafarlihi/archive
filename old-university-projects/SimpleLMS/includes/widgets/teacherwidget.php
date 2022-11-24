					<?php
					$teacherid = $_SESSION['id'];
					$classes = array();
					$i = 0;
					
					$result = mysql_query("SELECT COUNT(1) FROM `classes` WHERE `teacherid` = '$teacherid'");
					$num_rows = mysql_result($result, 0, 0);
					
					while ($i < $num_rows){
					$classes[$i] = mysql_result(mysql_query("SELECT `id` FROM `classes` WHERE `teacherid` = '$teacherid'"), $i, 'id');
					$i++;
					}
					?>
					
		<div class="widget">
                <h2>Classes You Manage:</h2>
                <div class="inner">
					<ul>
					<?php 
						if (empty($classes) === true){
						echo "You are not registered as instructor in any class. Please contact the site administrator.";
					}
					?>
					<?php 
					foreach ($classes as $id){
					?>
                                        <br>
					<a class="myButton" style="display: inline-block; width: 113px;" href="../../admin/manageclasses.php?id=<?php echo "$id";?>">
					<?php
					$str = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$id'"), 0, 'name');
					echo $str;
					?>
					</a><br>
					<?php
					}
					?>
					</ul>	
                </div>
            </div>
