					<?php
					$id = $_SESSION['id'];
					$classes = array();
					$i = 0;
					$result = mysql_query("SELECT COUNT(1) FROM `participation` WHERE `studentid` = '$id'");
					$num_rows = mysql_result($result, 0, 0);
					while ($i < $num_rows){
					$classes[$i] = mysql_result(mysql_query("SELECT `classid` FROM `participation` WHERE `studentid` = '$id'"), $i, 'classid');
					$i++;
					}
					?>
		<div class="widget">
                <h2>Enrolled Classes</h2>
                <div class="inner">
					<ul>
					<?php 
						if (empty($classes) === true){
						echo "You are not enlisted in any class. Please consult your instructor.";
					}
					?>
					<?php 
					foreach ($classes as $classid){
					?>
					<br>
					<br>
					<a class="myButton" href="../../student/classes.php?id=<?php echo "$classid";?>">
					<?php
					$classname = mysql_result(mysql_query("SELECT `name` FROM `classes` WHERE `id` = '$classid'"), 0, 'name');
					echo $classname;
					?>
					</a><br>
					<?php
					}
					?>
					</ul>	
                </div>
            </div>
