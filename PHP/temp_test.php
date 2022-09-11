
<?php
// DB 접속
$con=mysqli_connect("127.0.0.1","park","134625Wo@","esp_db");
// 접속 실패 시 메시지 나오게 하기
if (mysqli_connect_errno($con))
{ echo "MySQL접속 실패: " . mysqli_connect_error(); }

// 기본 클라이언트 문자 집합 설정하기
mysqli_set_charset($con,"utf8");
// 쿼리문 실행, 결과를 res에 저장
$res = mysqli_query($con, "select * from `project` ORDER BY `project`.`time` DESC");
// 결과를 배열로 변환하기 위한 변수 정의
$result = array();
// 쿼리문의 결과(res)를 배열형식으로 변환(result)
while($row = mysqli_fetch_array($res))
{ array_push($result, array('time'=>$row[0],'temp'=>$row[1],'hum'=>$row[2],'pm2.5'=>$row[4])); }
// DB 접속 종료
mysqli_close($con);
echo $result["time"];
?>

<script src="//www.google.com/jsapi"></script>
<script>
    let data = <?= json_encode($row) ?>;
    let options = <?= json_encode($row[0]) ?>;
    google.load('visualization', '1.0', {'packages':['corechart']});
    google.setOnLoadCallback(function() {
        let chart = new google.visualization.ColumnChart(document.querySelector('#chart_div'));
        chart.draw(google.visualization.arrayToDataTable(data), options);
    });
</script>
<div id="chart_div"></div>
