import 'package:flutter/material.dart';
import 'package:sound_test/pages/sound_1.dart';
import 'package:sound_test/pages/sound_2.dart';
import 'package:sound_test/pages/sound_3.dart';

class homePage extends StatelessWidget {
  const homePage({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: AppBarExample(),
    );
  }
}

class AppBarExample extends StatelessWidget {
  const AppBarExample({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('音效測試'),
      ),
      body: const Center(
        child: Column(children: [
            SizedBox(height: 10.0,),
            button_sound1(),
            SizedBox(height: 10.0,),
            button_sound2(),
            SizedBox(height: 10.0,),
            button_sound3()
        ],)
      ),
    );
  }
}


class button_sound1 extends StatelessWidget{
  const button_sound1({super.key});

  /*定義位置*/
  @override
  Widget build(BuildContext context){
    return Center(
        child: ElevatedButton(
          onPressed: (){
            Navigator.push(context,
                MaterialPageRoute(builder: (context) => sound1_Page()));
          },
          child: const Text("鐘"),
        ));
  }
}


class button_sound2 extends StatelessWidget{
  const button_sound2({super.key});

  /*定義位置*/
  @override
  Widget build(BuildContext context){
    return Center(
        child: ElevatedButton(
          onPressed: (){
            Navigator.push(context,
                MaterialPageRoute(builder: (context) => sound2_Page()));
          },
          child: const Text("木魚"),
        ));
  }
}

class button_sound3 extends StatelessWidget{
  const button_sound3({super.key});

  /*定義位置*/
  @override
  Widget build(BuildContext context){
    return Center(
        child: ElevatedButton(
          onPressed: (){
            Navigator.push(context,
                MaterialPageRoute(builder: (context) => sound3_Page()));
          },
          child: const Text("乳滑"),
        ));
  }
}