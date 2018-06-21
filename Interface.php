<head>
	<meta http-equiv="refresh" content="3">  // initialization every three seconds

</head>
<html>
	<title>Paking Area</title>  //title name Paking Area 
	<span style="color:white"> //set font color white 
	
<font size=30>&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp;&nbsp; &nbsp;Parking Area</font>
     <h1 class="my-4" > //Word spacing;
	<br>
        <small>&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;
		            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 			&nbsp;  Area1  //Word spacing
		            &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 			&nbsp; &nbsp;&nbsp; &nbsp;  
		            Area2//Word spacing
	      <small>
    </h1>
</span>
<body>
	
	
<body background="totoro_background.jpg"> // Wallpaper 
</body>

<?php
	$db_host="localhost"; //db host 
	$db_user="root"; // db user
	$db_passwd="kkkk"; //db password
	$db_name="KKKK"; //db name
	$tab= "&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; //Word spacing
		&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 
		&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 			&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 			&nbsp;&nbsp;";;
		
	define('PHP_TAB',"\t");
	$conn = mysqli_connect($db_host,$db_user,$db_passwd,$db_name);	//mysql connect

	if(mysqli_connect($conn)){ //Exception handling
		echo "failed : ",mysqli_connect_error();
	}else{

	}
	echo "$tab";//Word spacing
	echo "$tab";//Word spacing
		$result = mysqli_query($conn,"SELECT * FROM PARKING"); //db query
		while($row = mysqli_fetch_array($result)){// Repetition 
			if($row['DO']==0){		
				echo "<img src='oimage.jpg'/>"; // O image print
			}	
			else if($row['DO']==1){
				echo "<img src='ximage.jpg'/>"; // X image print
			}	
			else //Exception handling
				echo "error";
		}
		
			
	mysqli_close($conn); //sql close

?>
</html>
