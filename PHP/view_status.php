
<?php
// DB 접속
$con=mysqli_connect("127.0.0.1","park","134625Wo@","esp_db");
// 접속 실패 시 메시지 나오게 하기
if (mysqli_connect_errno($con))
{ echo "MySQL접속 실패: " . mysqli_connect_error(); }

// 기본 클라이언트 문자 집합 설정하기
mysqli_set_charset($con,"utf8");
// 쿼리문 실행, 결과를 res에 저장
$res = mysqli_query($con, "select * from `project_status`");
// 결과를 배열로 변환하기 위한 변수 정의
$result = array();
// 쿼리문의 결과(res)를 배열형식으로 변환(result)
while($row = mysqli_fetch_array($res))
{ array_push($result, array('status'=>$row[0],'R'=>$row[1],'G'=>$row[2],'B'=>$row[3])); }
// 배열형식의 결과를 json으로 변환
echo json_encode(array("result"=>$result),JSON_UNESCAPED_UNICODE);
// DB 접속 종료
mysqli_close($con);
?>


