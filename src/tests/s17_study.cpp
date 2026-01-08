#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>
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
  std::string config_file = "../config/sciurus17.yaml";

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

  int n = 10;
  for (int i = 0; i < n; i++) {
    if (!hardware.sync_read("right_arm")) {
      std::cerr << "right_armグループのsync readに失敗しました." << std::endl;
      break;
    }
    if (!hardware.sync_read("right_hand")) {
      std::cerr << "right_handグループのsync readに失敗しました." << std::endl;
      break;
    }
    if (!hardware.sync_read("left_arm")) {
      std::cerr << "left_armグループのsync readに失敗しました." << std::endl;
      break;
    }
    if (!hardware.sync_read("left_hand")) {
      std::cerr << "left_handグループのsync readに失敗しました." << std::endl;
      break;
    }
    if (!hardware.sync_read("torso")) {
      std::cerr << "torsoグループのsync readに失敗しました." << std::endl;
      break;
    }

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

    std::vector<double> diff_right_arm_positions(right_arm_positions.size(), 0.1 / n);
    add_left_to_right_vector(diff_right_arm_positions, right_arm_positions);
    hardware.set_positions("right_arm", right_arm_positions);
    if (!hardware.sync_write("right_arm")) {
      std::cerr << "right_armグループのsync writeに失敗しました." << std::endl;
      break;
    }
    std::vector<double> diff_right_hand_positions(right_hand_positions.size(), 0.1 / n);
    add_left_to_right_vector(diff_right_hand_positions, right_hand_positions);
    hardware.set_positions("right_hand", right_hand_positions);
    if (!hardware.sync_write("right_hand")) {
      std::cerr << "right_handグループのsync writeに失敗しました." << std::endl;
      break;
    }
    std::vector<double> diff_left_arm_positions(left_arm_positions.size(), 0.1 / n);
    add_left_to_right_vector(diff_left_arm_positions, left_arm_positions);
    hardware.set_positions("left_arm", left_arm_positions);
    if (!hardware.sync_write("left_arm")) {
      std::cerr << "left_armグループのsync writeに失敗しました." << std::endl;
      break;
    }
    std::vector<double> diff_left_hand_positions(left_hand_positions.size(), 0.1 / n);
    add_left_to_right_vector(diff_left_hand_positions, left_hand_positions);
    hardware.set_positions("left_hand", left_hand_positions);
    if (!hardware.sync_write("left_hand")) {
      std::cerr << "left_handグループのsync writeに失敗しました." << std::endl;
      break;
    }
    std::vector<double> diff_torso_positions(torso_positions.size(), 0.1 / n);
    add_left_to_right_vector(diff_torso_positions, torso_positions);
    hardware.set_positions("torso", torso_positions);
    if (!hardware.sync_write("torso")) {
      std::cerr << "torsoグループのsync writeに失敗しました." << std::endl;
      break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10 * 1000 / n));
  }

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

  std::cout << "Sciurus17との接続を解除します." << std::endl;
  hardware.disconnect();
  return 0;
}
