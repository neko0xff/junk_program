import 'package:flutter/material.dart';
import 'package:audioplayers/audioplayers.dart';

AudioPlayer player = AudioPlayer();

void playSoundEffect() async {
  await player.play(AssetSource('sound/clock_1.wav'));
  await player.resume();
}

class sound1_Page extends StatefulWidget {
  const sound1_Page({super.key});

  @override
  State<sound1_Page> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<sound1_Page> {
  int _counter = 0;

  void _incrementCounter() {
    setState(() {
      _counter++;
    });
    playSoundEffect();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: Theme.of(context).colorScheme.inversePrimary,
        title: Text("鐘声"),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              '己按下的次數: $_counter ',
              style: Theme.of(context).textTheme.headlineMedium,
            ),
          ],
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: '輸出',
        child: const Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}