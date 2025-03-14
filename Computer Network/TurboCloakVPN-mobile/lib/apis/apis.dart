import 'dart:convert';
import 'dart:developer';

import 'package:http/http.dart';
import 'package:turbocloakvpn/models/vpn.dart';
import 'package:http/http.dart' as http;
import 'package:uuid/uuid.dart';

class APIs {
  static Future<List<Vpn>> getVPNServers() async {
    final List<Vpn> vpnList = [];

    try {
      final response = await get(Uri.parse('http://16.171.236.191:8000/servers'));
      if (response.statusCode == 200) {
        final jsonData = json.decode(response.body);
        final List<dynamic> serverList = jsonData['server_list'];

        for (var server in serverList) {
          Vpn vpn = Vpn.fromJson(server);
          vpnList.add(vpn);
        }
      } else {
        // Handle error if the API call fails
        throw Exception('Failed to fetch VPN list: ${response.statusCode}');
      }
    } catch (e) {
      log('\ngetVPNServersE: $e');
    }
    return vpnList;
  }

  static Future<Map<String, String>> createOpenVPNClient() async {
    String? uuid;
    uuid = const Uuid().v4();

    try {
      final response = await http
          .get(Uri.parse('http://16.171.236.191:8000/create?id=$uuid'));

      if (response.statusCode == 200) {
        final responseBodyMap = jsonDecode(response.body);

        // Request successful, return the response body as a long string

        return {
          'uuid': uuid,
          'openVPNConfig': responseBodyMap['content'],
        };
      } else {
        // Request failed, throw an exception or handle the error accordingly
        throw Exception(
            'Failed to create OpenVPN client: ${response.statusCode}');
      }
    } catch (e) {
      // Catch any network or server errors
      throw Exception('Failed to create OpenVPN client: $e');
    }
  }

  static Future<void> deleteClient(String uuid) async {
    try {
      // Perform the POST request
      final response = await http
          .get(Uri.parse('http://16.171.236.191:8000/revoke?id=$uuid'));

      // Check if the request was successful (200 OK)
      if (response.statusCode == 200) {
        // Server returned a successful response
      } else {
        // Server returned an error response
        throw Exception('Failed to delete client with UUID: $uuid');
      }
    } catch (e) {
      // Exception occurred during the request
      throw Exception('Failed to delete OpenVPN client: $e');
    }
  }
}
