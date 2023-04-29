#include "menu.h"
#include "imguipp_v2.h"
#include "Windows.h"

char inputusername[128];
char inputpassword[128];
char inputkey[128];

//void Menu::RenderLogin() {
//	if (!globals::loggedIn) {
//		ImGui::SetNextWindowSize(ImVec2(400, 250), ImGuiCond_Always);
//		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.20f, 0.25f, 0.30f, 1.00f));
//		ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.13f, 0.16f, 0.20f, 1.00f));
//		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.13f, 0.16f, 0.20f, 1.00f));
//		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.13f, 0.16f, 0.20f, 1.00f));
//		ImGui::Begin("Login", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
//
//		ImGui::Spacing();
//
//		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.16f, 0.20f, 0.24f, 1.00f));
//		ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.13f, 0.16f, 0.20f, 1.00f));
//		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.87f, 0.87f, 0.87f, 1.00f));
//		float windowWidth = ImGui::GetWindowWidth();
//		float itemWidth = 600.0f; // adjust this to the desired width of the input boxes
//		float padding = (windowWidth - itemWidth) / 2.0f;
//
//		ImGui::SetCursorPosX(padding);
//		ImGui::Text("Username");
//		ImGui::SameLine();
//		ImGui::SetCursorPosX(padding + ImGui::GetWindowWidth() - itemWidth);
//		ImGui::InputText("##username", inputusername, 128);
//		ImGui::Spacing();
//		ImGui::SetCursorPosX(padding);
//		ImGui::Text("Password");
//		ImGui::SameLine();
//		ImGui::SetCursorPosX(padding + ImGui::GetWindowWidth() - itemWidth);
//		ImGui::InputText("##password", inputpassword, 128, ImGuiInputTextFlags_Password);
//
//		ImGui::PopStyleColor(3);
//		ImGui::Spacing();
//		if (ImGui::Button("Login", ImVec2(ImGui::GetContentRegionAvailWidth(), 30)))
//		{
//			// Perform login authentication here
//			if (1==1)
//			{
//				globals::loggedIn = true;
//				ImGui::CloseCurrentPopup();
//			}
//			else
//			{
//				// Show error message
//				ImGui::OpenPopup("Login Error");
//			}
//		}
//
//		// Error message popup
//		if (ImGui::BeginPopupModal("Login Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
//		{
//			ImGui::Text("Invalid username or password");
//			ImGui::Spacing();
//
//			if (ImGui::Button("OK", ImVec2(120, 0)))
//			{
//				ImGui::CloseCurrentPopup();
//			}
//
//			ImGui::EndPopup();
//		}
//
//		ImGui::End();
//		ImGui::PopStyleColor(4);
//	}
//}

bool show_login = true;
bool show_register = false;
ImVec2 window_size{ 600, 600 };



//void Menu::RenderLogin() {
//
//	if (!globals::loggedIn && globals::active) {
//		ImGui::SetNextWindowSize(window_size);
//		ImGui::Begin("Test", &globals::active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//		{
//			ImGui::SetCursorPos(ImVec2(726, 5));
//			if (ImGui::Selectable("X", false, ImGuiSelectableFlags_None)) {
//				ImGui::OpenPopup("Confirm Close");
//			}
//
//			if (ImGui::BeginPopupModal("Confirm Close", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
//				ImGui::Text("Are you sure you want to exit?");
//				if (ImGui::Button("Yes", ImVec2(120, 0))) {
//					ImGui::CloseCurrentPopup();
//					globals::active = false;
//					ExitProcess(0);
//				}
//				ImGui::SameLine();
//				if (ImGui::Button("No", ImVec2(120, 0))) {
//					ImGui::CloseCurrentPopup();
//				}
//				ImGui::EndPopup();
//			}
//
//			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054, 0.054, 0.054, 255));
//			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082, 0.078, 0.078, 255));
//			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);
//			{
//				ImGui::SetCursorPos(ImVec2(222, 83));
//				ImGui::BeginChild("##MainPanel", ImVec2(300, 276), true);
//				{
//					if (show_login)
//					{
//						ImGui::SetCursorPos(ImVec2(118, 20));
//						ImGui::TextDisabled("Welcome Back");
//
//						ImGui::SetCursorPos(ImVec2(97, 35));
//						ImGui::Text("Log into your account");
//
//						ImGui::PushItemWidth(260.f);
//						{
//							ImGui::SetCursorPos(ImVec2(22, 79));
//							ImGui::TextDisabled("Username");
//
//							ImGui::SetCursorPos(ImVec2(20, 95));
//							ImGui::InputText("##Username", inputusername, 128);
//						}
//						ImGui::PopItemWidth();
//
//						ImGui::PushItemWidth(260.f);
//						{
//							ImGui::SetCursorPos(ImVec2(22, 130));
//							ImGui::TextDisabled("Password");
//
//
//							ImGui::SetCursorPos(ImVec2(20, 146));
//							ImGui::InputText("##Passowrd", inputpassword, 128);
//						}
//						ImGui::PopItemWidth();
//
//						ImGui::SetCursorPos(ImVec2(22, 190));
//						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
//						if (ImGui::Button("Login", ImVec2(260.f, 30.f)))
//						{
//							globals::loggedIn = true;
//						}
//						ImGui::PopStyleVar();
//
//						ImGui::SetCursorPos(ImVec2(22, 240));
//						if (ImGui::Selectable("Register here.", false, ImGuiSelectableFlags_None)) {
//							show_register = true;
//							show_login = false;
//						}
//					}
//
//
//					if (show_register)
//					{
//						ImGui::SetCursorPos(ImVec2(118, 20));
//						ImGui::TextDisabled("Welcome Back");
//
//						ImGui::SetCursorPos(ImVec2(95, 35));
//						ImGui::Text("Register For An Account");
//
//						ImGui::PushItemWidth(260.f);
//						{
//							ImGui::SetCursorPos(ImVec2(22, 79));
//							ImGui::TextDisabled("Username");
//
//							ImGui::SetCursorPos(ImVec2(20, 95));
//							ImGui::InputText("##Username", inputusername, 128);
//						}
//						ImGui::PopItemWidth();
//
//						ImGui::PushItemWidth(260.f);
//						{
//							ImGui::SetCursorPos(ImVec2(22, 130));
//							ImGui::TextDisabled("Invite Key");
//
//							ImGui::SetCursorPos(ImVec2(20, 146));
//							ImGui::InputText("##InviteKey", inputkey, 128);
//						}
//						ImGui::PopItemWidth();
//
//						ImGui::SetCursorPos(ImVec2(22, 190));
//						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
//						if (ImGui::Button("Register", ImVec2(260.f, 30.f)))
//						{
//							show_login = true;
//							show_register = false;
//						}
//						ImGui::PopStyleVar();
//
//						ImGui::SetCursorPos(ImVec2(22, 240));
//						ImGui::TextDisabled("Already have an account? Sign in now!");
//					}
//
//				}
//				ImGui::EndChild();
//			}
//			ImGui::PopStyleColor(2);
//			ImGui::PopStyleVar(1);
//
//			ImGui::SetCursorPos(ImVec2(5, 445));
//		}
//		ImGui::End();
//	}
//	
//}

auto current_panel = 0;
const float padding{ 10 };
//void Menu::RenderLogin() {
//	if (!globals::loggedIn && globals::active) {
//		const float padding{ 10 };
//
//		ImGui::SetWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - ImGui::GetWindowSize().x) * 0.5f, (ImGui::GetIO().DisplaySize.y - ImGui::GetWindowSize().y) * 0.5f));
//		ImGui::Begin("Login Window", &globals::active, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//		{
//			/*ImGui::BeginChild("##TopPanel", ImVec2(window_size.x - padding * 20, window_size.y - padding * 20), false);
//			{
//				ImGui::SetCursorPos(ImVec2(padding, padding));
//				ImGuiPP::CenterTextEx(ICON_FA_TIMES_CIRCLE, 205, 0, 0);
//				if (ImGui::IsItemClicked()) {
//					globals::active = false;
//					ExitProcess(0);
//				}
//			}*/
//			
//
//		
//
//			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.054f, 0.054f, 0.054f, 1.0f));
//			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.082f, 0.078f, 0.078f, 1.0f));
//			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3.f);
//			{
//				ImGui::SetCursorPos(ImVec2(padding * 7, padding * 6));
//				ImGui::BeginChild("##MainPanel", ImVec2(window_size.x - padding * 14, window_size.y - padding * 12), true);
//				{
//					switch (current_panel) {
//					case 0:
//					{
//						ImGui::SetCursorPos(ImVec2(window_size.x / 3, padding * 3));
//						ImGui::TextDisabled("Welcome Back");
//
//						ImGui::SetCursorPos(ImVec2(window_size.x / 3 - padding, padding * 5));
//						ImGui::Text("Log into your account");
//
//						ImGui::PushItemWidth(window_size.x / 2);
//						{
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 9));
//							ImGui::Text("Username");
//
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 11));
//							ImGui::InputText("##Username", inputusername, sizeof(inputusername));
//						}
//
//						ImGui::PushItemWidth(window_size.x / 2);
//						{
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 15));
//							ImGui::Text("Password");
//
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 17));
//							ImGui::InputText("##Password", inputpassword, sizeof(inputpassword), ImGuiInputTextFlags_Password);
//						}
//						
//
//						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 21));
//
//						
//
//						if (ImGui::Button("Login", ImVec2(window_size.x / 2, 30.f)))
//						{
//							if (strlen(inputusername) < 3 || strlen(inputpassword) < 3) {
//								MessageBoxA(NULL, "Please enter a valid username and password.", "Error", MB_OK | MB_ICONERROR);
//							}
//							else {
//								if (1==1) {
//									globals::loggedIn = true;
//									globals::active = false;
//								}
//								else {
//									MessageBoxA(NULL, "Invalid username or password.", "Error", MB_OK | MB_ICONERROR);
//								}
//							}
//						}
//
//					
//
//						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 25));
//
//						
//
//						if (ImGui::Button("Register", ImVec2(window_size.x / 2, 30.f)))
//						{
//							current_panel = 1;
//						}
//
//
//						break;
//
//					}
//					case 1:
//					{
//
//						ImGui::SetCursorPos(ImVec2(window_size.x / 3 - padding, padding * 5));
//						ImGui::Text("Register For An Account");
//						ImGui::Spacing();
//						ImGui::PushItemWidth(window_size.x / 2);
//						{
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 9));
//							ImGui::TextDisabled("Username");
//
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 11));
//							ImGui::InputText("##Username", inputusername, 128);
//						}
//						ImGui::PopItemWidth();
//						ImGui::Spacing();
//						ImGui::PushItemWidth(260.f);
//						{
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 15));
//							ImGui::TextDisabled("Password");
//
//							ImGui::SetCursorPos(ImVec2(padding * 2, padding * 17));
//							ImGui::InputText("##Password", inputpassword, 128);
//						}
//						ImGui::PopItemWidth();
//
//						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 21));
//						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);
//						if (ImGui::Button("Register", ImVec2(260.f, 30.f)))
//						{
//							current_panel = 0;
//						}
//						ImGui::PopStyleVar();
//						ImGui::Spacing();
//						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 25));
//						if (ImGui::Selectable("Already have an account? Login.", false, ImGuiSelectableFlags_None)) {
//							current_panel = 0;
//						}
//					}
//
//
//					}
//				}
//				ImGui::EndChild();
//			}
//
//			ImGui::SetCursorPos(ImVec2(5, 445));
//
//		}
//
//		ImGui::End();
//
//	}
//
//}

void Menu::Render()
{
	static ImVec4 active = ImGuiPP::ToVec4(219, 190, 0, 255);
	static ImVec4 inactive = ImGuiPP::ToVec4(255, 255,255, 255);
	if (globals::loggedIn) {

		//login page

		ImGui::BeginChild("##LeftSide", ImVec2(200, ImGui::GetContentRegionAvail().y), TRUE);

		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 75);

			ImGui::PushStyleColor(ImGuiCol_Text, globals::menuTab == 0 ? active : inactive);
			ImGuiPP::CenterTextEx(ICON_FA_STAR, 205, 0, 0);
			if (ImGui::IsItemClicked()) globals::menuTab = 0;

			ImGui::NewLine();
			ImGui::PushStyleColor(ImGuiCol_Text, globals::menuTab == 1 ? active : inactive);
			ImGuiPP::CenterTextEx(ICON_FA_DATABASE, 205, 0, 0);
			if (ImGui::IsItemClicked()) globals::menuTab = 1;

			ImGui::NewLine();
			ImGui::PushStyleColor(ImGuiCol_Text, globals::menuTab == 2 ? active : inactive);
			ImGuiPP::CenterTextEx(ICON_FA_COGS, 205, 0, 0);
			if (ImGui::IsItemClicked()) globals::menuTab = 2;

			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			ImGui::NewLine();
			ImGuiPP::CenterTextEx(ICON_FA_TIMES_CIRCLE, 205, 0, 0);
			if (ImGui::IsItemClicked()) ExitProcess(0);

			ImGui::PopStyleColor(4);
		}


		ImGui::EndChild();
		ImGuiPP::Linevertical();

		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			ImGui::BeginChild("##RightSide", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY()), TRUE);
			ImGui::PopStyleColor();
			{
				switch (globals::menuTab)
				{

				case 0:
					ImGuiPP::CenterText("3r3n.3x3 L04D3R", 1, TRUE);
					ImGui::NewLine();
					ImGui::TextColored(ImColor(220, 190, 0, 255), "Version: 1.0");
					ImGui::Text("Status: Undetected");
					break;

				case 1:
					ImGui::ListBoxHeader("##GamesChoice", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY() - 36.5));
					for (int i = 0; i < globals::games.size(); i++)
					{
						const bool selected = (globals::gameIndex == i);
						if (ImGui::Selectable(globals::games[i].c_str(), selected))
							globals::gameIndex = i;
						if (selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::ListBoxFooter();

					if (ImGui::Button(("Launch " + globals::games[globals::gameIndex]).c_str(), ImVec2(ImGuiPP::GetX(), 33)))
					{
						ShowWindow(GetActiveWindow(), SW_HIDE);
						Sleep(2500);
						AllocConsole();
						freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
						ShowWindow(GetConsoleWindow(), SW_SHOW);
						printf("Injecting into %s...\n\n", globals::games[globals::gameIndex]);
						Sleep(1500);
						// inject code :) i will add soon :)
					}
					break;

				case 2:
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
					ImGui::Checkbox("Safe Injection", &G->SafeInjection);
					HELPMARKER("Safe Injection Will Make Sure Everything injected is timed correctly.");
					ImGui::Checkbox("Block reports", &G->Blockreports);
					HELPMARKER("Block reports will block any reports of your game crashing to the developers.");
					ImGui::Checkbox("Automatic Injection", &G->AutoInject);
					HELPMARKER("Automatic Injection will automatically wait for your game to load then inject.");
					ImGui::PopStyleVar();
					break;
				}
			}
			ImGui::EndChild();
		}
	}
	else{
		ImGui::BeginChild("##LeftSide", ImVec2(200, ImGui::GetContentRegionAvail().y), TRUE);

		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 75);

			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			ImGui::NewLine();
			ImGuiPP::CenterTextEx(ICON_FA_QUESTION_CIRCLE, 205, 0, 0);
			if (ImGui::IsItemClicked()) ShellExecute(0, 0, L"http://www.google.com", 0, 0, SW_SHOW);

			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			ImGui::NewLine();
			ImGuiPP::CenterTextEx(ICON_FA_TIMES_CIRCLE, 205, 0, 0);
			if (ImGui::IsItemClicked()) ExitProcess(0);

			ImGui::PopStyleColor(2);
		}


		ImGui::EndChild();
		ImGuiPP::Linevertical();

		{
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
			ImGui::BeginChild("##RightSide", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY()), TRUE);
			ImGui::PopStyleColor();
			{
				switch (current_panel) {
				case 0:
				{
					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Welcome Back").x) / 2);
					ImGui::TextDisabled("Welcome Back");

					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Log into your account").x) / 2);
					ImGui::Text("Log into your account");

					ImGui::PushItemWidth(window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 9));
						ImGui::Text("Username");

						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 11));
						ImGui::InputText("##Username", inputusername, sizeof(inputusername));
					}

					ImGui::PushItemWidth(window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 15));
						ImGui::Text("Password");

						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 17));
						ImGui::InputText("##Password", inputpassword, sizeof(inputpassword), ImGuiInputTextFlags_Password);
					}


					ImGui::SetCursorPos(ImVec2(padding * 2, padding * 21));



					if (ImGui::Button("Login", ImVec2(window_size.x / 2, 30.f)))
					{
						if (strlen(inputusername) < 3 || strlen(inputpassword) < 3) {
							MessageBoxA(NULL, "Please enter a valid username and password.", "Error", MB_OK | MB_ICONERROR);
						}
						else {
							if (1 == 1) {
								globals::loggedIn = true;
								globals::active = false;
							}
							else {
								MessageBoxA(NULL, "Invalid username or password.", "Error", MB_OK | MB_ICONERROR);
							}
						}
					}



					ImGui::SetCursorPos(ImVec2(padding * 2, padding * 25));



					if (ImGui::Button("Register", ImVec2(window_size.x / 2, 30.f)))
					{
						current_panel = 1;
					}


					break;

				}
				case 1:
				{
					ImGui::Spacing();
					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Register For An Account").x) / 2);
					ImGui::Text("Register For An Account");
					ImGui::Spacing();
					ImGui::PushItemWidth(window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 9));
						ImGui::Text("Username");

						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 11));
						ImGui::InputText("##Username", inputusername, sizeof(inputusername));
					}

					ImGui::PushItemWidth(window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 15));
						ImGui::Text("Password");

						ImGui::SetCursorPos(ImVec2(padding * 2, padding * 17));
						ImGui::InputText("##Password", inputpassword, sizeof(inputpassword), ImGuiInputTextFlags_Password);
					}
					ImGui::PopItemWidth();

					ImGui::SetCursorPos(ImVec2(padding * 2, padding * 21));
					if (ImGui::Button("Register", ImVec2(window_size.x / 2, 30.f)))
					{
						current_panel = 0;
					}
					ImGui::Spacing();
					ImGui::SetCursorPos(ImVec2(padding * 2, padding * 25));
					if (ImGui::Selectable("Already have an account? Login.", false, ImGuiSelectableFlags_None)) {
						current_panel = 0;
					}
				}


				}
			}
			ImGui::EndChild();
		}

	}
	
}

void Menu::Theme()
{
	ImGuiStyle& Style = ImGui::GetStyle();
	auto Color = Style.Colors;
	
	Style.WindowMinSize     = ImVec2(600, 600);
	Style.WindowBorderSize  = 0;

	Style.ChildRounding     = 0;
	Style.FrameRounding     = 0;
	Style.ScrollbarRounding = 0;
	Style.GrabRounding		= 0;
	Style.PopupRounding		= 0;
	Style.WindowRounding	= 3;


	Color[ImGuiCol_WindowBg]            = ImColor(18, 18, 18, 255);
	
	Color[ImGuiCol_FrameBg]		        = ImColor(31, 31, 31, 255);
	Color[ImGuiCol_FrameBgActive]       = ImColor(41, 41, 41, 255);
	Color[ImGuiCol_FrameBgHovered]      = ImColor(41, 41, 41, 255);

	Color[ImGuiCol_Button]	            = ImColor(168, 50, 133);
	Color[ImGuiCol_ButtonActive]        = ImColor(168, 50, 133);
	Color[ImGuiCol_ButtonHovered]       = ImColor(168, 50, 133);

	Color[ImGuiCol_Border]              = ImColor(0, 0, 0, 0);
	Color[ImGuiCol_Separator]           = ImColor(36, 36, 36, 255);

	Color[ImGuiCol_ResizeGrip]		    = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripActive]    = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered]   = ImColor(30, 30, 30, 255);

	Color[ImGuiCol_ChildBg]			    = ImColor(26, 26, 26, 255);

	Color[ImGuiCol_ScrollbarBg]         = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrab]       = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);

	Color[ImGuiCol_Header]			    = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderActive]	    = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered]       = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark]		    = ImColor(255, 255, 255, 255);
}