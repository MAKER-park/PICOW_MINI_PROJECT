<?php 
// DB 접속 
$con=mysqli_connect("127.0.0.1","park","134625Wo@","esp_db"); 
// 접속 실패 시 메시지 나오게 하기 
if (mysqli_connect_errno($con)) 
{ echo "MySQL접속 실패: " . mysqli_connect_error(); } 

// 기본 클라이언트 문자 집합 설정하기 
mysqli_set_charset($con,"utf8"); 
// 쿼리문 실행, 결과를 res에 저장 
$res = mysqli_query($con, "SELECT * FROM `project` ORDER BY `time` DESC LIMIT 20"); 
// 결과를 배열로 변환하기 위한 변수 정의
$result = array(); 
// 쿼리문의 결과(res)를 배열형식으로 변환(result) 
while($row = mysqli_fetch_array($res)) 
{ array_push($result, array('time'=>$row[0],'temp'=>$row[1],'hum'=>$row[2],'pm1_0'=>$row[3],  'pm2_5'=>$row[4], 'pm10'=>$row[5])); } 
// 배열형식의 결과를 json으로 변환 
//echo json_encode(array($result),JSON_UNESCAPED_UNICODE); //이렇게 사용하면 칼럼이 2개로 잡힌다.
//echo json_encode($result); 
echo json_encode($result[0][1]);
// DB 접속 종료 
mysqli_close($con); 
?>
<?php
$data = [
    ['원소', '밀도'],
    ['구리', 8.94],
    ['은', 10.49],
    ['금', 19.30],
    ['백금', 21.45],
];
$options = [
    'title' => '귀금속 밀도 (단위: g/cm³)',
    'width' => 400, 'height' => 500
];
//echo json_encode($data);
//echo json_encode($temp);
?>
<script src="//www.google.com/jsapi"></script>
<script>

    //let data = <?= json_encode($temp) ?>;
    //let options = <?= json_encode($time) ?>;
    //google.load('visualization', '1.0', {'packages':['corechart']});
    //google.setOnLoadCallback(function() {
    //    let chart = new google.visualization.ColumnChart(document.querySelector('#chart_div'));
    //    chart.draw(google.visualization.arrayToDataTable(data), options);
    //});
</script>
<div id="chart_div"></div>



