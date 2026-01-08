#include <chrono>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <nlohmann/json.hpp>
#include "rt_manipulators_cpp/hardware.hpp"

void print_positions(const std::vector<double>& positions) {
  std::cout << "[";
  for (int i = 0; i < positions.size(); i++) {
    std::cout << positions[i];
    if (i != positions.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

int add_left_to_right_vector(const std::vector<double>& left, std::vector<double>& right) {
  if (left.size() != right.size()) {
    std::cerr << "ベクトルのサイズが一致しません." << std::endl;
    return -1;
  }
  for (int i = 0; i < left.size(); i++) {
    right[i] += left[i];
  }
  return 0;
}

int main() {
  std::cout << "Sciurus17のトルクをON/OFFするサンプルです." << std::endl;

  std::string port_name = "/dev/ttyUSB0";
  int baudrate = 3000000;  // 3Mbps
  std::string config_file = "config/sciurus17.yaml";
  std::string data_path = "data/control_amp_30deg_T_5s_t-samp_10ms.jsonl";
  int t_samp = 10;  // msec
  std::ifstream file(data_path);
  if (!file.is_open()) {
    std::cerr << "データファイルの読み込みに失敗しました: "
              << data_path << std::endl;
    return -1;
  }
  std::string line;

  std::cout << "Sciurus17(";
  std::cout << "ポート:" << port_name;
  std::cout << " ボーレート:" << std::to_string(baudrate);
  std::cout << ")に接続します." << std::endl;

  rt_manipulators_cpp::Hardware hardware(port_name);
  if (!hardware.connect(baudrate)) {
    std::cerr << "ロボットとの接続に失敗しました." << std::endl;
    return -1;
  }

  std::cout << "コンフィグファイル:" << config_file << "を読み込みます." << std::endl;
  if (!hardware.load_config_file(config_file)) {
    std::cerr << "コンフィグファイルの読み込みに失敗しました." << std::endl;
    return -1;
  }

  if (!hardware.write_max_acceleration_to_group("right_arm", 0.5 * M_PI)) {
    std::cerr << "right_armグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("right_arm", 0.5 * M_PI)) {
    std::cerr << "right_armグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("right_hand", 0.5 * M_PI)) {
    std::cerr << "right_handグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("right_hand", 0.5 * M_PI)) {
    std::cerr << "right_handグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("left_arm", 0.5 * M_PI)) {
    std::cerr << "left_armグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("left_arm", 0.5 * M_PI)) {
    std::cerr << "left_armグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("left_hand", 0.5 * M_PI)) {
    std::cerr << "left_handグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("left_hand", 0.5 * M_PI)) {
    std::cerr << "left_handグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_acceleration_to_group("torso", 0.5 * M_PI)) {
    std::cerr << "torsoグループの最大加速度を設定できませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_max_velocity_to_group("torso", 0.5 * M_PI)) {
    std::cerr << "torsoグループの最大速度を設定できませんでした." << std::endl;
    return -1;
  }

  if (!hardware.write_position_pid_gain_to_group("right_arm", 800, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 800, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 800, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 800, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 800, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }

  if (!hardware.torque_on("right_arm")) {
    std::cerr << "right_armグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("right_hand")) {
    std::cerr << "right_handグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("left_arm")) {
    std::cerr << "left_armグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("left_hand")) {
    std::cerr << "left_handグループのトルクをONできませんでした." << std::endl;
    return -1;
  }
  if (!hardware.torque_on("torso")) {
    std::cerr << "torsoグループのトルクをONできませんでした." << std::endl;
    return -1;
  }

  std::cout << "ファイルから読み込んだ最初の目標値に移動します." << std::endl;
  std::getline(file, line);
  nlohmann::json json = nlohmann::json::parse(line);
  double time = json["time"];
  auto right_arm = json["joint"]["right_arm"].get<std::vector<double>>();
  auto right_hand = json["joint"]["right_hand"].get<std::vector<double>>();
  auto left_arm = json["joint"]["left_arm"].get<std::vector<double>>();
  auto left_hand = json["joint"]["left_hand"].get<std::vector<double>>();
  auto torso = json["joint"]["torso"].get<std::vector<double>>();
  hardware.set_positions("right_arm", right_arm);
  hardware.set_positions("right_hand", right_hand);
  hardware.set_positions("left_arm", left_arm);
  hardware.set_positions("left_hand", left_hand);
  hardware.set_positions("torso", torso);
  if (!hardware.sync_write("right_arm")) {
    std::cerr << "right_armグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("right_hand")) {
    std::cerr << "right_handグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("left_arm")) {
    std::cerr << "left_armグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("left_hand")) {
    std::cerr << "left_handグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  if (!hardware.sync_write("torso")) {
    std::cerr << "torsoグループのsync writeに失敗しました." << std::endl;
    return -1;
  }
  std::cout << "5秒間スリープして動作完了を待ちます." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "read/writeスレッドを起動します." << std::endl;
  std::vector<std::string> group_names = {
      "right_arm", "right_hand", "left_arm", "left_hand", "torso"};
  if (!hardware.start_thread(group_names, std::chrono::milliseconds(t_samp))) {
    std::cerr << "スレッドの起動に失敗しました." << std::endl;
    return -1;
  }

  while (std::getline(file, line)) {
    nlohmann::json json = nlohmann::json::parse(line);
    double time = json["time"];
    auto right_arm = json["joint"]["right_arm"].get<std::vector<double>>();
    auto right_hand = json["joint"]["right_hand"].get<std::vector<double>>();
    auto left_arm = json["joint"]["left_arm"].get<std::vector<double>>();
    auto left_hand = json["joint"]["left_hand"].get<std::vector<double>>();
    auto torso = json["joint"]["torso"].get<std::vector<double>>();

    hardware.set_positions("right_arm", right_arm);
    hardware.set_positions("right_hand", right_hand);
    hardware.set_positions("left_arm", left_arm);
    hardware.set_positions("left_hand", left_hand);
    hardware.set_positions("torso", torso);

    std::vector<double> right_arm_positions;
    if (!hardware.get_positions("right_arm", right_arm_positions)) {
      std::cerr << "right_armグループのサーボ角度の取得に失敗しました." << std::endl;
      break;
    } else {
      std::cout << "right_armグループのサーボ角度 (rad): ";
      print_positions(right_arm_positions);
    }
    std::vector<double> right_hand_positions;
    if (!hardware.get_positions("right_hand", right_hand_positions)) {
      std::cerr << "right_handグループのサーボ角度の取得に失敗しました." << std::endl;
      break;
    } else {
      std::cout << "right_handグループのサーボ角度 (rad): ";
      print_positions(right_hand_positions);
    }
    std::vector<double> left_arm_positions;
    if (!hardware.get_positions("left_arm", left_arm_positions)) {
      std::cerr << "left_armグループのサーボ角度の取得に失敗しました." << std::endl;
      break;
    } else {
      std::cout << "left_armグループのサーボ角度 (rad): ";
      print_positions(left_arm_positions);
    }
    std::vector<double> left_hand_positions;
    if (!hardware.get_positions("left_hand", left_hand_positions)) {
      std::cerr << "left_handグループのサーボ角度の取得に失敗しました." << std::endl;
      break;
    } else {
      std::cout << "left_handグループのサーボ角度 (rad): ";
      print_positions(left_hand_positions);
    }
    std::vector<double> torso_positions;
    if (!hardware.get_positions("torso", torso_positions)) {
      std::cerr << "torsoグループのサーボ角度の取得に失敗しました." << std::endl;
      break;
    } else {
      std::cout << "torsoグループのサーボ角度 (rad): ";
      print_positions(torso_positions);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(t_samp));
  }
  std::cout << "スレッドを停止します." << std::endl;
  hardware.stop_thread();

  std::cout
      << "サーボ位置制御PIDゲインに(5, 0, 0)を書き込み、脱力させます."
      << std::endl;
  if (!hardware.write_position_pid_gain_to_group("right_arm", 5, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 5, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 5, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 5, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 5, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  std::cout << "5秒間スリープします." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));

  if (!hardware.torque_off("right_arm")) {
    std::cerr << "right_armグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("right_hand")) {
    std::cerr << "right_handグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("left_arm")) {
    std::cerr << "left_armグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("left_hand")) {
    std::cerr << "left_handグループのトルクをOFFできませんでした." << std::endl;
  }
  if (!hardware.torque_off("torso")) {
    std::cerr << "torsoグループのトルクをOFFできませんでした." << std::endl;
  }

  if (!hardware.write_position_pid_gain_to_group("right_arm", 800, 0, 0)) {
    std::cerr << "right_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("right_hand", 800, 0, 0)) {
    std::cerr << "right_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_arm", 800, 0, 0)) {
    std::cerr << "left_armグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("left_hand", 800, 0, 0)) {
    std::cerr << "left_handグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  if (!hardware.write_position_pid_gain_to_group("torso", 800, 0, 0)) {
    std::cerr << "torsoグループにPIDゲインを書き込めませんでした." << std::endl;
    return -1;
  }
  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "Sciurus17との接続を解除します." << std::endl;
  hardware.disconnect();
  return 0;
}
