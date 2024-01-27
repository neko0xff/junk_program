// ignore_for_file: avoid_web_libraries_in_flutter, use_key_in_widget_constructors, camel_case_types
import 'package:flutter/material.dart';
import 'package:sound_test/pages/home.dart';
import 'package:sound_test/pages/sound_1.dart';
import 'package:sound_test/pages/sound_2.dart';
import 'package:sound_test/pages/sound_3.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: '声音測試',
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
        useMaterial3: true,
      ),
      home: const homePage(),
        routes: {
          "/home": (context) => const homePage(),
          "/clock": (context) => const sound1_Page(),
          "/sound2": (context) => const sound2_Page(),
          "/sound3": (context) => const sound3_Page(),
        }
    );
  }
}


