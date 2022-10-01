import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_charts/charts.dart';
import 'dart:async';
import 'dart:math' as math;
import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:intl/intl.dart';
import 'second.dart';



void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(

        primarySwatch: Colors.blue,
      ),
      home: MyHomePage(title: 'CHRAI_PICO_PROJECT_AIR_CAR'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();

}

class _MyHomePageState extends State<MyHomePage> {
  late List<LiveData> chartData;
  late ChartSeriesController _chartSeriesController;
  DateFormat dateFormat = DateFormat("yyyy-MM-dd HH:mm:ss");

  @override
  void initState() {
    chartData = getChartData();
    Timer.periodic(const Duration(seconds: 1), updateDataSource);
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(

        child: Scaffold(

          appBar: AppBar(
            title: const Text('CHRAI_PICO_PROJECT_AIR_CAR'),
            centerTitle: true,
            backgroundColor: Colors.greenAccent,
          ),
            body: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                SfCartesianChart(
                    series: <LineSeries<LiveData, int>>[
                      LineSeries<LiveData, int>(
                        onRendererCreated: (ChartSeriesController controller) {
                          _chartSeriesController = controller;
                        },
                        dataSource: chartData,
                        color: const Color.fromRGBO(192, 108, 132, 1),
                        xValueMapper: (LiveData sales, _) => sales.time,
                        yValueMapper: (LiveData sales, _) => sales.speed,
                      )
                    ],
                    primaryXAxis: NumericAxis(
                        majorGridLines: const MajorGridLines(width: 0),
                        edgeLabelPlacement: EdgeLabelPlacement.shift,
                        interval: 3,
                        title: AxisTitle(text: 'Date')),
                    primaryYAxis: NumericAxis(
                        axisLine: const AxisLine(width: 0),
                        majorTickLines: const MajorTickLines(size: 0),
                        title: AxisTitle(text: 'PM2.5 (Mbps)'))),
              ],
            ),
            floatingActionButton: FloatingActionButton(
              child: Icon(Icons.palette),
              onPressed: (){
                print("move color picker page");
                change_state();

                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => COLOR_Screen()),
                );
              },
            )
        )

    );
  }

  int time = 19;
  var counter = 0;
  var myJson_time;
  var myJson_pm;
  void updateDataSource(Timer timer) {
    counter++;
    // print("counter : " + counter.toString());
    if(counter >= 10){
      print("update!");
      counter = 0;
      LoadData();
    }

  }

  @override
  void LoadData() async {
    try {
      http.Response response = await http.get(
        Uri.parse(
          'http://cloud.park-cloud.co19.kr/pico_project/view2.php',
        ),
      );
      String jsonData = response.body;
      print(jsonData);
      myJson_time = jsonDecode(jsonData)[0]['time'];
      myJson_pm = int.parse(jsonDecode(jsonData)[0]['pm2'].toString());
      // print("data_time : "+myJson_time.toString());
      // print("data_pm : "+myJson_pm.toString());
      // print("time : " + time.toString());
      chartData.add(LiveData(time++, myJson_pm.toInt()));
      if(time > 19){
        chartData.removeAt(0);
        _chartSeriesController.updateDataSource(
            addedDataIndex: chartData.length - 1, removedDataIndex: 0);
      }

    } catch (e) {
      print('url 정보 불러오기 실패 ' + e.toString());
    }
  }

  void change_state() async {
    try {
      http.Response response = await http.get(
        Uri.parse(
          'http://cloud.park-cloud.co19.kr/pico_project/update_status.php?&status=1&R=0&G=0&B=0',
        ),
      );
      print("go to url to change state");
      String jsonData = response.body;
      print(jsonData);
    } catch (e) {
      print('url 정보 불러오기 실패 ' + e.toString());
    }
  }

  List<LiveData> getChartData() {
    return <LiveData>[
      LiveData(0, 0),
      LiveData(1, 0),
      LiveData(2, 0),
      LiveData(3, 0),
      LiveData(4, 0),
      LiveData(5, 0),
      LiveData(6, 0),
      LiveData(7, 0),
      LiveData(8, 0),
      LiveData(9, 0),
      LiveData(10, 0),
      LiveData(11, 0),
      LiveData(12, 0),
      LiveData(13, 0),
      LiveData(14, 0),
      LiveData(15, 0),
      LiveData(16, 0),
      LiveData(17, 0),
      LiveData(18, 0)
    ];
  }
}

class LiveData {
  LiveData(this.time, this.speed);
  final int time;
  final num speed;
}