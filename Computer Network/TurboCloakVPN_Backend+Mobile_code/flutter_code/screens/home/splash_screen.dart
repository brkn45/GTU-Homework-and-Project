import 'package:flutter/material.dart';
import 'package:turbocloakvpn/screens/home/home_screen.dart';

import '../../main.dart';

class SplashScreen extends StatefulWidget {
  const SplashScreen({super.key});

  @override
  State<SplashScreen> createState() => _SplashScreenState();
}

class _SplashScreenState extends State<SplashScreen> {
  @override
  Widget build(BuildContext context) {
    mq = MediaQuery.of(context).size;
    Future.delayed(const Duration(seconds: 3), () {
      Navigator.push(
          context, MaterialPageRoute(builder: (context) => const HomeScreen()));
    });
    return Scaffold(
      body: Stack(
        children: [
          Positioned(
            left: mq.width * .3,
            top: mq.height * .3,
            width: mq.width * .4,
            child: Image.asset(
              'images/ic_logo.png',
              height: 200,
              width: 200,
              fit: BoxFit.cover,
            ),
          ),
          Positioned(
            bottom: mq.height * .15,
            width: mq.width,
            child: const Text(
              'Turbo Cloak VPN',
              textAlign: TextAlign.center,
              style: TextStyle(color: Colors.white, letterSpacing: 1),
            ),
          ),
        ],
      ),
    );
  }
}
