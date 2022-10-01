import 'package:flutter/material.dart';
import 'package:flutter_colorpicker/flutter_colorpicker.dart';
import './pickers/hsv_picker.dart';
import './pickers/material_picker.dart';
import './pickers/block_picker.dart';
import 'package:http/http.dart' as http;


void main() => runApp(const MaterialApp(home: COLOR_Screen()));

class COLOR_Screen extends StatefulWidget {
  const COLOR_Screen({Key? key}) : super(key: key);

  @override
  State<StatefulWidget> createState() => _MyAppState();
}

class _MyAppState extends State<COLOR_Screen> {
  bool lightTheme = true;
  Color currentColor = Colors.amber;
  List<Color> currentColors = [Colors.yellow, Colors.green];
  List<Color> colorHistory = [];

  void changeColor(Color color) => setState(() => currentColor = color);
  void changeColors(List<Color> colors) => setState(() => currentColors = colors);


  @override
  Widget build(BuildContext context) {
    final foregroundColor = useWhiteForeground(currentColor) ? Colors.white : Colors.black;
    return AnimatedTheme(
      data: lightTheme ? ThemeData.light() : ThemeData.dark(),
      child: Builder(builder: (context) {
        return DefaultTabController(
          length: 5,
          child: Scaffold(
            floatingActionButton: FloatingActionButton.extended(
              onPressed: () => setState(() => lightTheme = !lightTheme),
              icon: Icon(lightTheme ? Icons.dark_mode_rounded : Icons.light_mode_rounded),
              label: Text(lightTheme ? 'Night' : '  Day '),
              backgroundColor: currentColor,
              foregroundColor: foregroundColor,
              elevation: 100,
            ),
            floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
            appBar: AppBar(
              title: const Text('PICO COLOR SELECT PAGE'),
              centerTitle: true,
              backgroundColor: currentColor,
              foregroundColor: foregroundColor,
              automaticallyImplyLeading: false,
            ),
            body: TabBarView(
              children: <Widget>[
                HSVColorPickerExample(
                  pickerColor: currentColor,
                  onColorChanged: changeColor,
                  colorHistory: colorHistory,
                  onHistoryChanged: (List<Color> colors) => colorHistory = colors,
                ),
              ],
            ),
          ),
        );
      }),
    );
  }
}