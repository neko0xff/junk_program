import 'package:flutter/material.dart';
import 'package:audioplayers/audioplayers.dart';

AudioPlayer player = AudioPlayer();

void playSoundEffect() async {
  await player.play(AssetSource('sound/sound_3.wav'));
  await player.resume();
}

class sound3_Page extends StatefulWidget {
  const sound3_Page({super.key});

  @override
  State<sound3_Page> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<sound3_Page> {
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
        title: const Text("乳滑"),
      ),
      body: Container(
        decoration: BoxDecoration(
          image: DecorationImage(
            image: AssetImage("assets/images/img02.jpg"),
            fit: BoxFit.cover,
          ),
        ),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.start,
          children: <Widget>[
            SizedBox(height: 5.0),
            Text(
              '我們懷念他',
              style: const TextStyle(fontWeight: FontWeight.bold,color: Colors.red,fontSize: 25),
            ),
            SizedBox(height: 10.0),
            Text(
              '己按下的次數: $_counter ',
              style: const TextStyle(fontWeight: FontWeight.bold,color: Colors.red,fontSize: 25),
            ),
            SizedBox(height: 10.0),
            const img01(),
          ],
        ),
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: '輸出',
        child: const Icon(Icons.add),
      ), // This trailing comma makes auto-formatting nicer for build methods.
    );
  }
}

class img01 extends StatelessWidget{
  const img01({super.key});

  @override
  Widget build(BuildContext context){
    return const Center(
      child: Image(
        image: AssetImage('assets/images/img01.png'),
        width: 300.0,
        height: 300.0
      ),
    );
  }
}

