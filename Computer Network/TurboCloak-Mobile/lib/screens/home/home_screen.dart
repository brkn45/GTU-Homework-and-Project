import 'dart:async';
import 'dart:convert';
import 'package:crypto/crypto.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'package:turbocloakvpn/apis/apis.dart';

import 'package:turbocloakvpn/models/vpn_config.dart';
import 'package:turbocloakvpn/services/vpn_engine.dart';

import '../../main.dart';
import '../../models/vpn.dart';

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  Duration duration = const Duration();
  Timer? timer;
  bool isActive = false;
  bool locationSelected = false;
  String location = '';
  String flagPNG = '';
  List<Vpn> vpnList = [];
  String openVPNBase64 = '';
  String uuidsha256 = '';

  List<String> items = List.generate(20, (index) => "Item ${index + 1}");
  @override
  void initState() {
    super.initState();
  }

  void updateLocation(String newLocation, String newFlagPNG) {
    setState(() {
      locationSelected = true;
      location = newLocation;
      flagPNG = newFlagPNG;
      isActive = false;
    });
  }

  void startTimer() {
    timer = Timer.periodic(const Duration(seconds: 1), (_) => addTime());
  }

  void reset() {
    if (!isActive) {
      setState(() => duration = const Duration());
    }
  }

  void stopTimer() {
    reset();
    setState(() => timer?.cancel());
  }

  void addTime() {
    const addSeconds = 1;

    setState(() {
      final seconds = duration.inSeconds + addSeconds;

      duration = Duration(seconds: seconds);
    });
  }

  void manageTimer() {
    if (isActive) {
      startTimer();
    } else {
      stopTimer();
    }
  }

  void connectClick() async {
    Map<String, String> result = await APIs.createOpenVPNClient();
    setState(() {
      uuidsha256 = generateSha256(result['uuid']!);
    });

    final vpnConfig = VpnConfig(
      country: location,
      username: 'vpn',
      password: 'vpn',
      config: result['openVPNConfig']!,
    );

    VpnEngine.startVpn(vpnConfig);
  }

  void exit() async {
    await VpnEngine.stopVpn();
  }

  void deleteClient() async {
    if (uuidsha256 != '') {
      await APIs.deleteClient(uuidsha256);
    }
  }

  String generateSha256(String input) {
    var bytes = utf8.encode(input); // Encode the input string to bytes
    var sha256Hash = sha256.convert(bytes); // Generate the SHA-256 hash
    return sha256Hash.toString(); // Convert the hash to a string representation
  }

  Widget buildTimer() {
    String twoDigits(int n) => n.toString().padLeft(2, '0');
    final minutes = twoDigits(duration.inMinutes.remainder(60));
    final seconds = twoDigits(duration.inSeconds.remainder(60));
    final hours = twoDigits(duration.inHours);

    return Text(
      '$hours : $minutes : $seconds',
      style: const TextStyle(fontSize: 18),
    );
  }

  @override
  Widget build(BuildContext context) {
    VpnEngine.vpnStageSnapshot();

    double screenHeight = mq.height;
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false,
        backgroundColor: Colors.grey.withOpacity(0.3),
        elevation: 3,
        centerTitle: true,
        title: const Text(
          "TurboCloakVPN",
        ),
      ),
      //LOCATION DISPLAY
      bottomNavigationBar: SafeArea(
        child: Container(
          color: Colors.grey.withOpacity(0.3),
          height: 60,
          padding: EdgeInsets.symmetric(horizontal: screenHeight * .02),
          child: Row(
            children: [
              locationSelected == true
                  ? CircleAvatar(
                      radius: 20,
                      backgroundImage: NetworkImage(flagPNG),
                    )
                  : const Icon(
                      CupertinoIcons.globe,
                      color: Colors.white,
                      size: 24,
                    ),
              const SizedBox(
                width: 10,
              ),
              Text(
                locationSelected == true
                    ? location.toUpperCase()
                    : 'Select Location',
                style: const TextStyle(
                  color: Colors.white,
                  fontSize: 16,
                  fontWeight: FontWeight.w500,
                ),
              ),
              const Spacer(),
              InkWell(
                onTap: () async {
                  {
                    await showModalBottomSheet(
                        context: context,
                        builder: (context) {
                          return FutureBuilder(
                              future: APIs.getVPNServers(),
                              builder: (context, snapshot) {
                                if (snapshot.connectionState ==
                                    ConnectionState.waiting) {
                                  return const Center(
                                    child: CircularProgressIndicator(),
                                  );
                                } else if (snapshot.connectionState ==
                                    ConnectionState.done) {
                                  List<Vpn> vpnList =
                                      snapshot.data as List<Vpn>;
                                  return ListView.builder(
                                    itemCount: vpnList.length,
                                    padding: const EdgeInsets.all(8),
                                    itemBuilder: (context, index) {
                                      return Card(
                                        elevation: 5,
                                        shape: RoundedRectangleBorder(
                                            borderRadius:
                                                BorderRadius.circular(15)),
                                        child: ListTile(
                                          contentPadding:
                                              const EdgeInsets.all(8),
                                          leading: CircleAvatar(
                                            radius: 28,
                                            backgroundImage: NetworkImage(
                                                vpnList[index]
                                                    .countryFlagPNG
                                                    .toString()),
                                          ),
                                          trailing: InkWell(
                                            borderRadius:
                                                BorderRadius.circular(28),
                                            onTap: () {
                                              if (locationSelected &&
                                                  isActive) {
                                                exit();
                                                manageTimer();
                                              }
                                              updateLocation(
                                                  vpnList[index]
                                                      .countryName
                                                      .toString()
                                                      .toLowerCase(),
                                                  vpnList[index]
                                                      .countryFlagPNG
                                                      .toString());
                                              Navigator.pop(context);
                                            },
                                            child: const CircleAvatar(
                                              backgroundColor: Color.fromARGB(
                                                  255, 146, 144, 144),
                                              child: Icon(
                                                Icons
                                                    .keyboard_arrow_left_rounded,
                                                color: Colors.white,
                                                size: 28,
                                              ),
                                            ),
                                          ),
                                          title: Text(vpnList[index]
                                              .countryName
                                              .toString()),
                                          // subtitle: Text(vpnList[index]
                                          //     .ip
                                          //     .toString()
                                          //     .split(":")[0]),
                                        ),
                                      );
                                    },
                                  );
                                }
                                return Container();
                              });
                        });
                  }
                },
                child: const CircleAvatar(
                  backgroundColor: Colors.grey,
                  child: Icon(
                    Icons.keyboard_arrow_down_rounded,
                    color: Colors.white,
                    size: 28,
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
      body: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 20),
        child: Column(
          children: [
            const SizedBox(
              height: 100,
            ),
            Semantics(
              button: true,
              child: locationSelected == true
                  ? InkWell(
                      onTap: () {
                        setState(() {
                          if (isActive) {
                            exit();
                            deleteClient();
                          } else {
                            connectClick();
                          }
                          isActive = !isActive;

                          manageTimer();
                        });
                      },
                      borderRadius: BorderRadius.circular(100),
                      child: Container(
                        padding: const EdgeInsets.all(16),
                        decoration: BoxDecoration(
                            shape: BoxShape.circle,
                            color: isActive == true
                                ? Colors.grey.withOpacity(.1)
                                : Colors.orange.withOpacity(.1)),
                        child: Container(
                          padding: const EdgeInsets.all(16),
                          decoration: BoxDecoration(
                              shape: BoxShape.circle,
                              color: isActive == true
                                  ? Colors.grey.withOpacity(.3)
                                  : Colors.orange.withOpacity(.3)),
                          child: Container(
                            width: screenHeight * .14,
                            height: screenHeight * .14,
                            decoration: BoxDecoration(
                                shape: BoxShape.circle,
                                color: isActive == true
                                    ? Colors.grey
                                    : Colors.orange),
                            child: Column(
                              mainAxisAlignment: MainAxisAlignment.center,
                              children: [
                                const Icon(
                                  Icons.power_settings_new_rounded,
                                  size: 28,
                                  color: Colors.white,
                                ),
                                const SizedBox(
                                  height: 4,
                                ),
                                Text(
                                  isActive == true
                                      ? 'Tap To Disconnect'
                                      : 'Tap To Connect',
                                  style: const TextStyle(
                                    fontSize: 12.5,
                                    color: Colors.white,
                                    fontWeight: FontWeight.w500,
                                  ),
                                ),
                              ],
                            ),
                          ),
                        ),
                      ),
                    )
                  : InkWell(
                      borderRadius: BorderRadius.circular(100),
                      child: Container(
                        padding: const EdgeInsets.all(16),
                        decoration: BoxDecoration(
                            shape: BoxShape.circle,
                            color: isActive == true
                                ? Colors.grey.withOpacity(.1)
                                : Colors.orange.withOpacity(.1)),
                        child: Container(
                          padding: const EdgeInsets.all(16),
                          decoration: BoxDecoration(
                              shape: BoxShape.circle,
                              color: isActive == true
                                  ? Colors.grey.withOpacity(.3)
                                  : Colors.orange.withOpacity(.3)),
                          child: Container(
                            width: screenHeight * .14,
                            height: screenHeight * .14,
                            decoration: BoxDecoration(
                                shape: BoxShape.circle,
                                color: isActive == true
                                    ? Colors.grey
                                    : Colors.orange),
                            child: Column(
                              mainAxisAlignment: MainAxisAlignment.center,
                              children: [
                                const Icon(
                                  Icons.power_settings_new_rounded,
                                  size: 28,
                                  color: Colors.white,
                                ),
                                const SizedBox(
                                  height: 4,
                                ),
                                Text(
                                  isActive == true
                                      ? 'Tap To Disconnect'
                                      : 'Tap To Connect',
                                  style: const TextStyle(
                                    fontSize: 12.5,
                                    color: Colors.white,
                                    fontWeight: FontWeight.w500,
                                  ),
                                ),
                              ],
                            ),
                          ),
                        ),
                      ),
                    ),
            ),
            const SizedBox(
              height: 20,
            ),
            Container(
              margin: EdgeInsets.only(top: screenHeight * 0.015),
              padding: const EdgeInsetsDirectional.symmetric(
                  vertical: 6, horizontal: 16),
              decoration: BoxDecoration(
                  color: isActive == true ? Colors.orange : Colors.grey,
                  borderRadius: BorderRadius.circular(15)),
              child: Text(
                isActive == true ? 'Connected' : 'Not Connected',
                style: const TextStyle(fontSize: 12.5, color: Colors.white),
              ),
            ),
            const SizedBox(
              height: 20,
            ),
            Center(
              child: buildTimer(),
            ),
          ],
        ),
      ),
    );
  }
}
