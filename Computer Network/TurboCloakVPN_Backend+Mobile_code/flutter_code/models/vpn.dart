class Vpn {
  late final String ip;
  late final String ping;
  late final String countryName;
  late final String countryFlagPNG;

  Vpn({
    required this.ip,
    required this.ping,
    required this.countryName,
    required this.countryFlagPNG,
  });

  Vpn.fromJson(Map<String, dynamic> json) {
    ip = json['IP'] ?? '';
    countryName = json['country_name'] ?? '';
    countryFlagPNG = json['country_flag_png'] ?? '';
  }

  Map<String, dynamic> toJson() {
    final data = <String, dynamic>{};
    data['IP'] = ip;
    data['country_name'] = countryName;
    data['country_flag_png'] = countryFlagPNG;
    return data;
  }
}
