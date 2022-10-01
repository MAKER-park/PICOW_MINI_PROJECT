import 'package:flutter/cupertino.dart' show CupertinoTextField;
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_colorpicker/flutter_colorpicker.dart';
import 'package:http/http.dart' as http;
import 'dart:async';

// Just an example of how to use/interpret/format text input's result.
void copyToClipboard(String input) {
  String textToCopy = input.replaceFirst('#', '').toUpperCase();
  if (textToCopy.startsWith('FF') && textToCopy.length == 8) {
    textToCopy = textToCopy.replaceFirst('FF', '');
  }
  Clipboard.setData(ClipboardData(text: '#$textToCopy'));
}

class HSVColorPickerExample extends StatefulWidget {
  const HSVColorPickerExample({
    Key? key,
    required this.pickerColor,
    required this.onColorChanged,
    this.colorHistory,
    this.onHistoryChanged,
  }) : super(key: key);

  final Color pickerColor;
  final ValueChanged<Color> onColorChanged;
  final List<Color>? colorHistory;
  final ValueChanged<List<Color>>? onHistoryChanged;

  @override
  State<HSVColorPickerExample> createState() => _HSVColorPickerExampleState();
}

class _HSVColorPickerExampleState extends State<HSVColorPickerExample> {

  // Picker 2
  bool _displayThumbColor2 = false;
  bool _enableAlpha2 = false;
  String R = " ";
  String G = " ";
  String B = " ";

  @override
  void get_state(){
    setState(() {
      print(widget.pickerColor.red.toString());
      print(widget.pickerColor.green.toString());
      print(widget.pickerColor.blue.toString());
    });
  }
  // Picker 4
  final textController =
      TextEditingController(text: '#2F19DC'); // The initial value can be provided directly to the controller.
  bool _enableAlpha4 = true;

  @override
  void dispose() {
    textController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return ListView(

      children: [
        Align(
          alignment: Alignment.topRight,
          child: FloatingActionButton(onPressed: (){
            //change state send
            print("send change state");
            change_state();
            Navigator.pop(context);
          },child: Text("Exit",style: TextStyle(color: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black),
          ),
            backgroundColor: widget.pickerColor,
            foregroundColor: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black,
          ),
        ),
        const Divider(),
        const SizedBox(height: 50),
        Text(
            "You chose COLOR is "+widget.pickerColor.toString(),
          textAlign: TextAlign.center,
          style: TextStyle(
            color: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black,
            backgroundColor: useWhiteForeground(widget.pickerColor) ? Colors.black : Colors.white,
            fontSize: 40,
          )
        ),

        Row(
          mainAxisSize: MainAxisSize.min,
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            ElevatedButton(
              onPressed: () {
                showDialog(
                  context: context,
                  builder: (BuildContext context) {
                    return AlertDialog(
                      titlePadding: const EdgeInsets.all(0),
                      contentPadding: const EdgeInsets.all(0),
                      shape: RoundedRectangleBorder(
                        borderRadius: MediaQuery.of(context).orientation == Orientation.portrait
                            ? const BorderRadius.vertical(
                                top: Radius.circular(800),
                                bottom: Radius.circular(100),
                              )
                            : const BorderRadius.horizontal(right: Radius.circular(800)),
                      ),
                      content: SingleChildScrollView(
                        child: HueRingPicker(
                          pickerColor: widget.pickerColor,
                          onColorChanged: widget.onColorChanged,
                          enableAlpha: _enableAlpha2,
                          displayThumbColor: _displayThumbColor2,
                        ),
                      ),
                    );
                  },
                );
              },
              child: Text(
                'PICO LED COLOR palette',
                style: TextStyle(color: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black),
              ),
              style: ElevatedButton.styleFrom(
                primary: widget.pickerColor,
                shadowColor: widget.pickerColor.withOpacity(1),
                elevation: 15,
              ),
            ),
          ],
        ),
        FloatingActionButton(onPressed: (){
          print(widget.pickerColor.red.toString());
          print(widget.pickerColor.green.toString());
          print(widget.pickerColor.blue.toString());
          change_COLOR(widget.pickerColor.red.toString(), widget.pickerColor.green.toString(), widget.pickerColor.blue.toString());
        },child: Text("apply",style: TextStyle(color: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black),
        ),
          backgroundColor: widget.pickerColor,
          foregroundColor: useWhiteForeground(widget.pickerColor) ? Colors.white : Colors.black,
        ),
      ],
    );
  }
}

@override
void change_COLOR(String R, String G, String B) async {
  try {
    http.Response response = await http.get(
      Uri.parse(
        "http://cloud.park-cloud.co19.kr/pico_project/update_status.php?&status=1&R="+R+"&G="+G+"&B="+B,
      ),
    );
    print("go to url to change color");
    String jsonData = response.body;
    print(jsonData);
  } catch (e) {
    print('url 정보 불러오기 실패 ' + e.toString());
  }
}

@override
void change_state() async {
  try {
    http.Response response = await http.get(
      Uri.parse(
        'http://cloud.park-cloud.co19.kr/pico_project/update_status.php?&status=0&R=0&G=0&B=0',
      ),
    );
    print("go to url to change state");
    String jsonData = response.body;
    print(jsonData);
  } catch (e) {
    print('url 정보 불러오기 실패 ' + e.toString());
  }
}