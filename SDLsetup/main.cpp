#include <SDL.h>
#include<iostream>
#include<stdio.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include<fstream>
#include <sstream>
#include"CAUTHU.H"
#include"TRANDAU.H"
#include"DOIBONG.H"
#include<vector>
#include<iomanip>
using namespace std;

#define NUM_BUTTONS 5
#define NUM_BUTTONS0 5
#define NUM_BUTTONS1 8
#define NUM_BUTTONS2 5
#define NUM_BUTTONSBACK 15
#define BUTTON_WIDTH 430
#define BUTTON_HEIGHT 50
#define BUTTON_SPACING 15
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

typedef struct {
	SDL_Rect rect;
	SDL_Texture* texture;
} Button;

Button buttons[NUM_BUTTONS];
Button buttons0[NUM_BUTTONS0];
Button buttons1[NUM_BUTTONS1];
Button buttons2[NUM_BUTTONS2];
Button buttonsBack[NUM_BUTTONSBACK];


void renderButton(SDL_Renderer* renderer, Button* button) {
	SDL_RenderCopy(renderer, button->texture, NULL, &button->rect);
}

bool isPointInRect(int x, int y, SDL_Rect* rect) {
	return (x >= rect->x && x <= rect->x + rect->w && y >= rect->y && y <= rect->y + rect->h);
}
//ham

void setDataCTFromdataDb(vector<CauThu>& listPlayerCT, const vector<doibong>& danhsachdoibong) {
	for (const auto& doibong : danhsachdoibong) {
		for (const auto& cauthu : doibong.getdscauthu()) {
			listPlayerCT.push_back(cauthu);
		}
	}
}

void setCTvaoDB(const CauThu& t, vector<CauThu>& danhsachcauthu) {
	danhsachcauthu.push_back(t);
}

void setDatDBFromFile(vector<doibong>& danhSachDoiBong) {
	ifstream file("E:\\dataD\\doibong.txt");
	if (file.is_open()) {
		int sl = 0;
		string line;
		string tenDoiBong, diaPhuong, huanLuyenVien;
		string id, fn, it, bi, he, we, po;
		while (getline(file, line)) {
			if (line.find("Ten doi bong: ") != string::npos) {
				tenDoiBong = line.substr(14);
			}
			else if (line.find("Dia phuong: ") != string::npos) {
				diaPhuong = line.substr(12);
			}
			else if (line.find("Huan luyen vien: ") != string::npos) {
				huanLuyenVien = line.substr(17);
			}
			vector<CauThu> danhsachcauthu;
			if (line.find("Danh sach cau thu: ") != string::npos) {
				sl = stoi(line.substr(19));
				getline(file, line);
				for (int i = 0; i < sl; i++) {
					for (int j = 0; j < 7; j++) {
						if (line.find("So CMND: ") != string::npos) {
							id = line.substr(9);
							getline(file, line);
						}
						else if (line.find("Ho ten: ") != string::npos) {
							fn = line.substr(8);
							getline(file, line);
						}
						else if (line.find("Quoc tich: ") != string::npos) {
							it = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Ngay sinh: ") != string::npos) {
							bi = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Chieu cao: ") != string::npos) {
							he = line.substr(11);
							getline(file, line);
						}
						else if (line.find("Can nang: ") != string::npos) {
							we = line.substr(10);
							getline(file, line);
						}
						else if (line.find("Vi tri thi dau: ") != string::npos) {
							po = line.substr(16);
							getline(file, line);
							getline(file, line);
							CauThu T(id, fn, it, bi, he, we, po, tenDoiBong);
							danhsachcauthu.push_back(T);
						}
					}
				}
				doibong doibong1(tenDoiBong, diaPhuong, huanLuyenVien, danhsachcauthu);
				danhSachDoiBong.push_back(doibong1);
			}
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void setDataTrandauFromFile(vector<TranDau>& danhsachtrandau) {
	ifstream file("E:\\dataD\\trandau.txt");
	if (file.is_open()) {
		int d, m, y;
		string sandau, t1, t2, tyso, line;
		while (getline(file, line)) {
			if (line.find("ngay : ") != string::npos) {
				d = stoi(line.substr(7));
			}
			else if (line.find("thang : ") != string::npos) {
				m = stoi(line.substr(8));
			}
			else if (line.find("nam : ") != string::npos) {
				y = stoi(line.substr(6));
			}
			else if (line.find("san dau : ") != string::npos) {
				sandau = line.substr(10);
			}
			else if (line.find("team 1 : ") != string::npos) {
				t1 = line.substr(9);
			}
			else if (line.find("team 2 : ") != string::npos) {
				t2 = line.substr(9);
			}
			else if (line.find("ty so : ") != string::npos) {
				tyso = line.substr(8);
				danhsachtrandau.push_back(TranDau(d, m, y, sandau, t1, t2, tyso));
			}
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void menu() {
	cout << "**********************************************" << endl;
	cout << "1. Hien thi thong tin 1 cau thu " << endl;
	cout << "2. Them moi cau thu " << endl;
	cout << "3. Xoa thong tin cau thu" << endl;
	cout << "4. Sua thong tin cau thu" << endl;
	cout << "5. Hien thi danh sach cau thu" << endl;
	cout << "6. Hien thi cau thu tre tuoi nhat" << endl;
	cout << "7. Hien thi cau thu cao nhat" << endl;
	cout << "8. Hien thi cau thu thap nhat" << endl;
	cout << "0. Quay lai" << endl;
	cout << "**********************************************" << endl;
}


void luuThongTinDoiBong(const vector<doibong>& danhSachDoiBong) {
	ofstream file("E:\\dataD\\doibong.txt");
	if (file.is_open()) {
		danhSachDoiBong.begin()->getdscauthu();
		for (const auto& doiBong : danhSachDoiBong) {
			file << "Ten doi bong: " << doiBong.getTenDoiBong() << endl;
			file << "Dia phuong: " << doiBong.getDiaPhuong() << endl;
			file << "Huan luyen vien: " << doiBong.getHuanLuyenVien() << endl;
			file << "Danh sach cau thu: " << doiBong.getdodaidscauthu() << endl;
			for (const auto& cauThu : doiBong.getdscauthu()) {
				file << "So CMND: " << cauThu.getID() << endl;
				file << "Ho ten: " << cauThu.getFullname() << endl;
				file << "Quoc tich: " << cauThu.getInternational() << endl;
				file << "Ngay sinh: " << cauThu.getBirth() << endl;
				file << "Chieu cao: " << cauThu.getHeight() << endl;
				file << "Can nang: " << cauThu.getWeight() << endl;
				file << "Vi tri thi dau: " << cauThu.getPosition() << endl;
				file << "--------------------------" << endl;
			}
			file << "--------------------------" << endl;
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

void luuThongTinCauThu(const vector<CauThu>& listPlayerCT) {
	ofstream file("E:\\dataD\\dsplayer.txt");
	if (file.is_open()) {
		for (const auto& cauThu : listPlayerCT) {
			file << "So CMND: " << cauThu.getID() << endl;
			file << "Ho ten: " << cauThu.getFullname() << endl;
			file << "Quoc tich: " << cauThu.getInternational() << endl;
			file << "Ngay sinh: " << cauThu.getBirth() << endl;
			file << "Chieu cao: " << cauThu.getHeight() << endl;
			file << "Can nang: " << cauThu.getWeight() << endl;
			file << "Vi tri thi dau: " << cauThu.getPosition() << endl;
			file << "Thuoc doi bong: " << cauThu.getTendoibong() << endl;
			file << "--------------------------" << endl;
		}
		file.close();
	}
	else {
		cout << "Khong the mo tep tin doibong.txt." << endl;
	}
}

//main
int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("SDL2 Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Font* font = TTF_OpenFont("VeraMoBd.ttf", 24);
	SDL_Color color = { 255, 255, 255 };

	const char* labels[NUM_BUTTONS] = { "Quan ly cau thu", "Quan ly doi bong", "Quan ly tran dau", "Tinh diem cho cac doi bong", "Thoat" };
	const char* labels0[NUM_BUTTONS0] = { "Them doi bong", "Sua doi bong", "Xoa doi bong", "Hien thi thong tin doi bong", "Quay lai" };
	const char* labels1[NUM_BUTTONS1] = { "Xem thong tin cau thu", "Them moi cau thu","Sua cau thu", "Xoa cau thu", "Hien thi cau thu tre tuoi nhat","Hien thi cau thu cao nhat", "Hien thi cau thu thap nhat", "Quay lai" };
	const char* labels2[NUM_BUTTONS2] = { "Them tran dau", "Xem tran dau trong ngay", "Xem tran dau trong thang", "Xem tat ca tran dau", "Quay lai" };
	const char* labelsBack[NUM_BUTTONSBACK] = { "Quay lai, Quay lai, Quay lai" };

	for (int i = 0; i < NUM_BUTTONS; i++) {
		//SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], color);
		//buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttons[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; // Căn giữa theo chiều ngang
		buttons[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS * BUTTON_HEIGHT - (NUM_BUTTONS - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); // Căn giữa theo chiều dọc
		buttons[i].rect.w = BUTTON_WIDTH;
		buttons[i].rect.h = BUTTON_HEIGHT;

		//SDL_FreeSurface(surface);
	}
	for (int i = 0; i < NUM_BUTTONS0; i++) {
		//SDL_Surface* surface = TTF_RenderText_Solid(font, labels0[i], color);
		//buttons0[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttons0[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; // Căn giữa theo chiều ngang
		buttons0[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS0 * BUTTON_HEIGHT - (NUM_BUTTONS0 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); // Căn giữa theo chiều dọc
		buttons0[i].rect.w = BUTTON_WIDTH;
		buttons0[i].rect.h = BUTTON_HEIGHT;

		//SDL_FreeSurface(surface);
	}
	for (int i = 0; i < NUM_BUTTONS1; i++) {
		//SDL_Surface* surface = TTF_RenderText_Solid(font, labels0[i], color);
		//buttons0[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttons1[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; // Căn giữa theo chiều ngang
		buttons1[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS1 * BUTTON_HEIGHT - (NUM_BUTTONS1 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); // Căn giữa theo chiều dọc
		buttons1[i].rect.w = BUTTON_WIDTH;
		buttons1[i].rect.h = BUTTON_HEIGHT;

		//SDL_FreeSurface(surface);
	}
	for (int i = 0; i < NUM_BUTTONS2; i++) {
		//SDL_Surface* surface = TTF_RenderText_Solid(font, labels0[i], color);
		//buttons0[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttons2[i].rect.x = (SCREEN_WIDTH - BUTTON_WIDTH) / 2; // Căn giữa theo chiều ngang
		buttons2[i].rect.y = (SCREEN_HEIGHT - NUM_BUTTONS2 * BUTTON_HEIGHT - (NUM_BUTTONS2 - 1) * BUTTON_SPACING) / 2 + i * (BUTTON_HEIGHT + BUTTON_SPACING); // Căn giữa theo chiều dọc
		buttons2[i].rect.w = BUTTON_WIDTH;
		buttons2[i].rect.h = BUTTON_HEIGHT;

		//SDL_FreeSurface(surface);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int i = 0; i < NUM_BUTTONSBACK; i++) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
		buttonsBack[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
		buttonsBack[i].rect.x = (SCREEN_WIDTH / 2) - 150 / 2; // Căn giữa theo chiều ngang
		buttonsBack[i].rect.y = 520;
		buttonsBack[i].rect.w = 150;
		buttonsBack[i].rect.h = 50;

		SDL_FreeSurface(surface);
	}
	Button inputTimcauthu = { 250, 100, 400, 50 };


	Button buttonback;
	buttonback.rect.x = (SCREEN_WIDTH / 2) - 150 / 2;
	buttonback.rect.y = 520;
	buttonback.rect.w = 150;
	buttonback.rect.h = 50;


	vector<TranDau> danhsachtrandau;
	vector<doibong> danhSachDoiBong;
	vector<CauThu> listPlayerCT;
	setDatDBFromFile(danhSachDoiBong);
	setDataCTFromdataDb(listPlayerCT, danhSachDoiBong);
	setDataTrandauFromFile(danhsachtrandau);

	bool running = true;
	bool running2 = true;
	bool running3 = true;
	bool running4 = true;
	bool running5 = true;
	bool running6 = true;

	SDL_Rect viewportMainMenu = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	Uint32 mainCurentTime = SDL_GetTicks();

	while (running) {
		SDL_Event event;
		int x, y;
		SDL_GetMouseState(&x, &y);
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đổi nền thành màu trắng
			SDL_RenderClear(renderer);
			SDL_RenderSetViewport(renderer, &viewportMainMenu);
			for (int i = 0; i < NUM_BUTTONS; i++) {
				SDL_Color textColor = { 0, 0, 0, 255 }; // Đổi chữ thành màu đen
				SDL_Surface* surface = TTF_RenderText_Solid(font, labels[i], textColor);
				buttons[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

				// Tạo một SDL_Rect riêng cho chữ
				SDL_Rect textRect;
				textRect.x = buttons[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; // Thêm một lề 10 pixel
				textRect.y = buttons[i].rect.y + 10;
				textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
				textRect.h = surface->h;

				// Vẽ nút và chữ

				if (isPointInRect(x, y, &buttons[i].rect)) {
					SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); // Màu cam khi hover
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng khi không hover
				}

				SDL_RenderFillRect(renderer, &buttons[i].rect);
				SDL_RenderCopy(renderer, buttons[i].texture, NULL, &textRect);

				// Vẽ viền cam cho nút
				SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
				SDL_RenderDrawRect(renderer, &buttons[i].rect);

				SDL_FreeSurface(surface);
			}
			for (int i = 0; i < NUM_BUTTONS; i++) {
				if (isPointInRect(x, y, &buttons[i].rect)) {
					//cout << "is hover" << endl;
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						cout << "button press " << i + 1 << endl;
						switch (i) {
						case 1:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu vẽ thành màu trang
							SDL_RenderClear(renderer); // Xóa màn hình
							while (running3) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS0; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 }; // Đổi chữ thành màu đen
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels0[i], textColor);
										buttons0[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

										// Tạo một SDL_Rect riêng cho chữ
										SDL_Rect textRect;
										textRect.x = buttons0[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; // Thêm một lề 10 pixel
										textRect.y = buttons0[i].rect.y + 10;
										textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
										textRect.h = surface->h;

										// Vẽ nút và chữ

										if (isPointInRect(x, y, &buttons0[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); // Màu cam khi hover
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng khi không hover
										}

										SDL_RenderFillRect(renderer, &buttons0[i].rect);
										SDL_RenderCopy(renderer, buttons0[i].texture, NULL, &textRect);

										// Vẽ viền cam cho nút
										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
										SDL_RenderDrawRect(renderer, &buttons0[i].rect);

										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS0; i++) {
										if (isPointInRect(x, y, &buttons0[i].rect)) {
											//cout << "is hover" << endl;
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 4:
													running3 = false;
													break;
												}
											}
										}
									}
									SDL_RenderPresent(renderer);
								}
							}
							break;
						}

						case 0:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu vẽ thành màu trang
							SDL_RenderClear(renderer); // Xóa màn hình
							while (running4) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS1; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 }; // Đổi chữ thành màu đen
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels1[i], textColor);
										buttons1[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

										// Tạo một SDL_Rect riêng cho chữ
										SDL_Rect textRect;
										textRect.x = buttons1[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; // Thêm một lề 10 pixel
										textRect.y = buttons1[i].rect.y + 10;
										textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
										textRect.h = surface->h;

										// Vẽ nút và chữ

										if (isPointInRect(x, y, &buttons1[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); // Màu cam khi hover
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng khi không hover
										}

										SDL_RenderFillRect(renderer, &buttons1[i].rect);
										SDL_RenderCopy(renderer, buttons1[i].texture, NULL, &textRect);

										// Vẽ viền cam cho nút
										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
										SDL_RenderDrawRect(renderer, &buttons1[i].rect);

										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS1; i++) {
										if (isPointInRect(x, y, &buttons1[i].rect)) {
											//cout << "is hover" << endl;
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 0:
												{
													const int NUM_ROWS = 2;
													const int NUM_COLS = 8;
													const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS) - 10;
													const int CELL_HEIGHT = (SCREEN_HEIGHT / 2) / (NUM_ROWS * 2.5);

													SDL_Surface* textSurface;
													SDL_Texture* textTexture;

													SDL_Surface* textSurface2;
													SDL_Texture* textTexture2;

													SDL_Surface* textSurface3;
													SDL_Texture* textTexture3;

													string inputText = " ";
													string inputText2;

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);

													//bool running = true;


													bool ispointerInputTimcauthu = false;
													Uint32 lastCursorToggleTime = 0;
													while (running6) {
														SDL_Event event;
														int x, y;
														SDL_GetMouseState(&x, &y);
														while (SDL_PollEvent(&event)) {
															if (event.type == SDL_QUIT) {
																return 0;
															}
															if (event.type == SDL_MOUSEBUTTONDOWN) {
																if (isPointInRect(x, y, &inputTimcauthu.rect)) {
																	cout << "ispointer" << endl;
																	lastCursorToggleTime = mainCurentTime - 1000;
																	ispointerInputTimcauthu = true;
																}
																else {
																	ispointerInputTimcauthu = false;
																}
																if (isPointInRect(x, y, &buttonsBack[0].rect)) {
																	running6 = false;
																}
															}

															if (event.type == SDL_KEYDOWN && ispointerInputTimcauthu) {

																if (event.key.keysym.sym == SDLK_RETURN && inputText.length() > 1) {
																	ispointerInputTimcauthu = false;
																	inputText2 = inputText;
																	inputText2.erase(0, 1);
																}
																if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 1) {
																	inputText.pop_back();
																}
															}

															if (event.type == SDL_TEXTINPUT && ispointerInputTimcauthu) {
																inputText += event.text.text;

															}
														}
														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderClear(renderer);
														SDL_RenderFillRect(renderer, &inputTimcauthu.rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &inputTimcauthu.rect);

														SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
														SDL_RenderFillRect(renderer, &buttonsBack[0].rect);
														SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
														SDL_RenderDrawRect(renderer, &buttonsBack[0].rect);
														SDL_Rect textRectBack0 = { buttonsBack[0].rect.x + 10, buttonsBack[0].rect.y + 10, buttonsBack[0].rect.w - 20, buttonsBack[0].rect.h - 20 };
														SDL_RenderCopy(renderer, buttonsBack[0].texture, NULL, &textRectBack0);

														// Vẽ văn bản nhập vào ô
														SDL_Color textColor = { 0, 0, 0, 255 };
														textSurface = TTF_RenderText_Solid(font, inputText.c_str(), textColor);
														textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
														SDL_Rect textRect = { inputTimcauthu.rect.x + 10, 110, textSurface->w, textSurface->h };
														SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

														textSurface2 = TTF_RenderText_Solid(font, "So CCCD", textColor);
														textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
														SDL_Rect textRect2 = { textRect.x - 140, 110, 100, textSurface->h };
														SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

														textSurface3 = TTF_RenderText_Solid(font, "NHAP CCCD CAN TIM", textColor);
														textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
														SDL_Rect textRect3 = { inputTimcauthu.rect.x, 50, textSurface3->w, textSurface3->h };
														SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);


														Uint32 currentTime = SDL_GetTicks();
														if ((currentTime - lastCursorToggleTime) >= 1000) {
															lastCursorToggleTime = currentTime;
														}

														if (((currentTime - lastCursorToggleTime) / 500) % 2 == 0 && ispointerInputTimcauthu) {
															// Vẽ con trỏ văn bản
															SDL_Rect cursorRect = { textSurface->w + (textRect.x), 110, 2, textSurface->h };
															SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
															SDL_RenderFillRect(renderer, &cursorRect);
														}
														// ve bang
														for (int i = 1; i < NUM_ROWS; i++) {

															for (int col = 0; col < NUM_COLS; col++) {
																SDL_Rect cellRect = { col * CELL_WIDTH, SCREEN_HEIGHT / 2 + i * CELL_HEIGHT , CELL_WIDTH, CELL_HEIGHT };									SDL_RenderDrawRect(renderer, &cellRect);
																SDL_RenderDrawRect(renderer, &cellRect);
																string text = "hello";
																/*if (col == 0) {
																	int t = i - 1;
																	text = "hello";
																}
																else if (col == 1) {
																	int t = i - 1;
																	text = "hello";

																}*/
																//string text = "Dữ liệu " + std::to_string(i) + "-" + std::to_string(col);

																SDL_Surface* textSurfaceTable = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
																SDL_Texture* textTextureTable = SDL_CreateTextureFromSurface(renderer, textSurfaceTable);

																int textWidth = textSurfaceTable->w;
																int textHeight = textSurfaceTable->h;

																SDL_Rect textRectTable = { col * CELL_WIDTH + (CELL_WIDTH - textWidth) / 2,
																					 i * CELL_HEIGHT + SCREEN_HEIGHT / 2 + (CELL_HEIGHT - textHeight) / 2,
																					 textWidth,
																					 textHeight };

																SDL_RenderCopy(renderer, textTextureTable, NULL, &textRectTable);

																SDL_FreeSurface(textSurfaceTable);
																SDL_DestroyTexture(textTextureTable);
																//SDL_RenderPresent(renderer);

															}
														}

														SDL_DestroyTexture(textTexture);
														SDL_FreeSurface(textSurface);
														SDL_DestroyTexture(textTexture2);
														SDL_FreeSurface(textSurface2);
														SDL_DestroyTexture(textTexture3);
														SDL_FreeSurface(textSurface3);

														SDL_RenderPresent(renderer);
													}

													SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
													SDL_RenderClear(renderer);
													cout << inputText2;
													break;
												}

												case 7:
												{
													running4 = false;
													break;
												}
												}
											}
										}
									}
								}
								//menu cauthu
								SDL_RenderPresent(renderer);
								running6 = true;
							}
							break;
						}
						case 2:
						{
							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu vẽ thành màu trang
							SDL_RenderClear(renderer); // Xóa màn hình
							while (running5) {
								SDL_Event event;
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									for (int i = 0; i < NUM_BUTTONS2; i++) {
										SDL_Color textColor = { 0, 0, 0, 255 }; // Đổi chữ thành màu đen
										SDL_Surface* surface = TTF_RenderText_Solid(font, labels2[i], textColor);
										buttons2[i].texture = SDL_CreateTextureFromSurface(renderer, surface);

										// Tạo một SDL_Rect riêng cho chữ
										SDL_Rect textRect;
										textRect.x = buttons2[i].rect.x + (BUTTON_WIDTH - surface->w) / 2; // Thêm một lề 10 pixel
										textRect.y = buttons2[i].rect.y + 10;
										textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
										textRect.h = surface->h;

										// Vẽ nút và chữ

										if (isPointInRect(x, y, &buttons2[i].rect)) {
											SDL_SetRenderDrawColor(renderer, 225, 240, 255, 0); // Màu cam khi hover
										}
										else {
											SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Màu trắng khi không hover
										}

										SDL_RenderFillRect(renderer, &buttons2[i].rect);
										SDL_RenderCopy(renderer, buttons2[i].texture, NULL, &textRect);

										// Vẽ viền cam cho nút
										SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
										SDL_RenderDrawRect(renderer, &buttons2[i].rect);

										SDL_FreeSurface(surface);
									}
									for (int i = 0; i < NUM_BUTTONS2; i++) {
										if (isPointInRect(x, y, &buttons2[i].rect)) {
											//cout << "is hover" << endl;
											if (event.type == SDL_MOUSEBUTTONDOWN) {
												cout << "button press " << i + 1 << endl;
												switch (i) {
												case 4:
													running5 = false;
													break;
												}
											}
										}
									}
									SDL_RenderPresent(renderer);
								}
							}
							break;
						}
						case 3:
						{
							struct dsdb {
								string ten;
								int diem;
							};
							vector<dsdb> _danhsachdoibong;
							for (auto& db : danhSachDoiBong) {
								dsdb t;
								t.ten = db.getTenDoiBong();
								t.diem = 0;
								_danhsachdoibong.push_back(t);
							}

							for (auto& td : danhsachtrandau) {
								int t1, t2;
								t1 = stoi(td.getTyso().substr(0));
								t2 = stoi(td.getTyso().substr(2));
								if (t1 > t2) {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam1() == db.ten) {
											db.diem += 3;
										}
									}
								}
								else if (t1 < t2) {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam2() == db.ten) {
											db.diem += 3;
										}
									}
								}
								else {
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam1() == db.ten) {
											db.diem += 1;
										}
									}
									for (auto& db : _danhsachdoibong) {
										if (td.getTeam2() == db.ten) {
											db.diem += 1;
										}
									}
								}
							}
							SDL_SetRenderDrawColor(renderer, 230, 214, 214, 1);
							//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Đặt màu vẽ thành màu trang
							SDL_RenderClear(renderer); // Xóa màn hình
							SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
							const int NUM_ROWS = _danhsachdoibong.size();
							const int NUM_COLS = 2;
							const int CELL_WIDTH = ((SCREEN_WIDTH) / NUM_COLS) - 10;
							const int CELL_HEIGHT = SCREEN_HEIGHT / (NUM_ROWS * 2.5);

							SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
							SDL_RenderFillRect(renderer, &buttonback.rect);
							SDL_Surface* surface = TTF_RenderText_Solid(font, "Quay lai", { 0,0,0,255 });
							buttonback.texture = SDL_CreateTextureFromSurface(renderer, surface);

							// Tạo một SDL_Rect riêng cho chữ
							SDL_Rect textRect;
							textRect.x = buttonback.rect.x + (buttonback.rect.w - surface->w) / 2; // Thêm một lề 10 pixel
							textRect.y = buttonback.rect.y + 10;
							textRect.w = surface->w; // Sử dụng chiều rộng và chiều cao của surface
							textRect.h = surface->h;
							// Vẽ viền cam cho nút
							SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam
							SDL_RenderDrawRect(renderer, &buttonback.rect);
							SDL_RenderCopy(renderer, buttonback.texture, NULL, &textRect);
							SDL_FreeSurface(surface);
							SDL_Rect viewport = { 0, 0, SCREEN_WIDTH - 9.9, SCREEN_HEIGHT - 100 };
							SDL_Rect content = { 10, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

							int scrollX = 0;
							int scrollY = 0;

							while (running2) {
								int x, y;
								SDL_GetMouseState(&x, &y);
								while (SDL_PollEvent(&event)) {
									if (event.type == SDL_QUIT) {
										return 0;
									}
									if (event.type == SDL_MOUSEWHEEL) {
										if (event.wheel.y >= 0) {
											if (scrollY >= 0) {
												scrollY -= 10;
											}
										}
										else if (event.wheel.y < 0) {
											if ((_danhsachdoibong.size() + 1) * CELL_HEIGHT > SCREEN_HEIGHT) {
												scrollY += 10;
											}
										}
									}
									if (isPointInRect(x, y, &buttonback.rect)) {
										if (event.type == SDL_MOUSEBUTTONDOWN) {
											running2 = false;
											cout << "is back " << endl;
										}
									}

								}
								SDL_RenderSetViewport(renderer, &viewport);

								SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
								SDL_RenderFillRect(renderer, &content);

								SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu cam

								for (int i = 0; i < 2; i++) {
									SDL_Rect cellRect = { content.x + i * CELL_WIDTH, content.y + 0 * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };									SDL_RenderDrawRect(renderer, &cellRect);
									string text;
									if (i == 0) {
										text = "Ten doi bong";
									}
									else if (i == 1) {
										text = "Diem";
									}
									SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
									SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

									int textWidth = textSurface->w;
									int textHeight = textSurface->h;

									SDL_Rect textRect = { i * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
															 0 * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
															 textWidth,
															 textHeight };

									SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

									SDL_FreeSurface(textSurface);
									SDL_DestroyTexture(textTexture);
									//SDL_RenderPresent(renderer);
								}

								for (int i = 1; i < _danhsachdoibong.size() + 1; i++) {
									//cout << setw(30) << left << _danhsachdoibong[i-1].ten << _danhsachdoibong[i-1].diem << endl;
									// 
									for (int col = 0; col < NUM_COLS; col++) {
										SDL_Rect cellRect = { content.x + col * CELL_WIDTH, content.y + i * CELL_HEIGHT - scrollY, CELL_WIDTH, CELL_HEIGHT };									SDL_RenderDrawRect(renderer, &cellRect);
										SDL_RenderDrawRect(renderer, &cellRect);
										string text;
										if (col == 0) {
											int t = i - 1;
											text = _danhsachdoibong[t].ten;
										}
										else if (col == 1) {
											int t = i - 1;
											text = to_string(_danhsachdoibong[t].diem);

										}
										//string text = "Dữ liệu " + std::to_string(i) + "-" + std::to_string(col);

										SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
										SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

										int textWidth = textSurface->w;
										int textHeight = textSurface->h;

										SDL_Rect textRect = { col * CELL_WIDTH + content.x + (CELL_WIDTH - textWidth) / 2,
															 i * CELL_HEIGHT + content.y + (CELL_HEIGHT - textHeight) / 2 - scrollY,
															 textWidth,
															 textHeight };

										SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

										SDL_FreeSurface(textSurface);
										SDL_DestroyTexture(textTexture);
										//SDL_RenderPresent(renderer);

									}
								}
								SDL_RenderPresent(renderer);

							}
							break;
						}
						case 4:
						{
							return 0;
							break;
						}
						}
					}
				}
			}
		}
		SDL_RenderPresent(renderer);
		running2 = true;
		running3 = true;
		running4 = true;
		running5 = true;
		//running6 = true;
	}
	
	for (int i = 0; i < NUM_BUTTONS; i++) {
		SDL_DestroyTexture(buttons[i].texture);
	}
	for (int i = 0; i < NUM_BUTTONS0; i++) {
		SDL_DestroyTexture(buttons0[i].texture);
	}
	for (int i = 0; i < NUM_BUTTONS1; i++) {
		SDL_DestroyTexture(buttons1[i].texture);
	}
	for (int i = 0; i < NUM_BUTTONS2; i++) {
		SDL_DestroyTexture(buttons2[i].texture);
	}
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
