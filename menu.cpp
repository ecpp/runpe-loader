#include "menu.h"
#include "imguipp_v2.h"
#include "globals.h"
#include <shellapi.h>
#include <thread>

void getUserInfoAsync() {
	std::this_thread::sleep_for(std::chrono::minutes(10));
	if (!globals::api.getUserInfo()) {
		//create message box
		MessageBoxA(NULL, "Failed to get user info", "Error", MB_OK);
		//close program
		globals::active = false;
		globals::loggedIn = false;
		ExitProcess(0);

	}
	if (!globals::api.checkLoaderVersion()) {
		//create message box
		MessageBoxA(NULL, "Please update your loader", "Error", MB_OK);
		//close program
		globals::active = false;
		globals::loggedIn = false;
		ExitProcess(0);
	}
}

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
					ImGui::TextColored(ImColor(220, 190, 0, 255), ("Version: " + globals::version).c_str());
					ImGui::TextColored(ImColor(220, 190, 0, 255), ("Beta Testing Enabled"));
					ImGui::Text("Contact: Lydonuis#3169");
					ImGui::NewLine();
					//{
					//	ImGui::Text("Activate License:");
					//	ImGui::PushItemWidth(ImGuiPP::GetX());
					//	ImGui::InputText("##License", globals::inputkey, sizeof(globals::inputkey));
					//}
					//if (ImGui::Button("Activate", ImVec2(ImGuiPP::GetX(), 33)))
					//{
					//	//do something
					//}
					break;

				case 1:
					
					if (globals::products.size() > 0) {
						ImGui::ListBoxHeader("##GamesChoice", ImVec2(ImGuiPP::GetX(), ImGuiPP::GetY() - 36.5));
						ImGui::Columns(1, NULL, false);
						for (int i = 0; i < globals::products.size(); i++)
						{
							//create 2x2 grid
							if (i % 2 == 0) {
								ImGui::Separator();
							}
							//display name
							ImGui::Text(("Product: " + globals::products[globals::gameIndex].getName()).c_str());
							//display status
							ImGui::Text(("Status: " + globals::products[globals::gameIndex].getStatus()).c_str());
							ImGui::Text(("Valid Until: " + globals::products[globals::gameIndex].getExpirationDate()).c_str());
							//display button
							if (ImGui::Button(("INJECT TO " + globals::products[globals::gameIndex].getName()).c_str(), ImVec2(ImGuiPP::GetX(), 33)))
							{
								if (globals::api.validateProduct(globals::products[globals::gameIndex].getId())) {								
									ShowWindow(GetActiveWindow(), SW_HIDE);
									
									AllocConsole();
									freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
									ShowWindow(GetConsoleWindow(), SW_SHOW);
									printf("Please wait... Injecting into %s...\n\n", globals::products[globals::gameIndex]);
									if (!globals::api.downloadFile(globals::products[globals::gameIndex].getId(), globals::products[globals::gameIndex].getName())) {
										MessageBoxA(NULL, "Download failed.", "Error", MB_OK);
									}
										
									

								}
								else {
									//create message box
									MessageBoxA(NULL, "Failed to validate product.", "Error", MB_OK);
									//close program
									
								}

							}

							ImGui::NextColumn();


						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::ListBoxFooter();

						
					}
					else{
						ImGui::Text("No Active License Found");
					}
					
					break;

				case 2:
					/*ImGui::PushStyleVar(ImGuiStyleVar_Frameglobals::padding, ImVec2(5, 5));
					ImGui::Checkbox("Safe Injection", &G->SafeInjection);
					HELPMARKER("Safe Injection Will Make Sure Everything injected is timed correctly.");
					ImGui::Checkbox("Block reports", &G->Blockreports);
					HELPMARKER("Block reports will block any reports of your game crashing to the developers.");
					ImGui::Checkbox("Automatic Injection", &G->AutoInject);
					HELPMARKER("Automatic Injection will automatically wait for your game to load then inject.");
					ImGui::PopStyleVar();*/
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
				switch (globals::menuTab) {
				case 3:
				{
					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Welcome Back").x) / 2);
					ImGui::TextDisabled("Welcome Back");

					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Log into your account").x) / 2);
					ImGui::Text("Log into your account");

					ImGui::PushItemWidth(globals::window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 9));
						ImGui::Text("Username");

						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 11));
						ImGui::InputText("##Username", globals::inputusername, sizeof(globals::inputusername));
					}

					ImGui::PushItemWidth(globals::window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 15));
						ImGui::Text("Password");

						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 17));
						ImGui::InputText("##Password", globals::inputpassword, sizeof(globals::inputpassword), ImGuiInputTextFlags_Password);
					}


					ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 21));



					if (ImGui::Button("Login", ImVec2(globals::window_size.x / 2, 30.f)))
					{
						if (strlen(globals::inputusername) < 3 || strlen(globals::inputpassword) < 3) {
							MessageBoxA(NULL, "Please enter a valid username and password.", "Error", MB_OK | MB_ICONERROR);
						}
						else {

							if (globals::api.login(globals::inputusername, globals::inputpassword, globals::hwid)==0) {
								if (globals::api.getUserInfo()) {
									//create thread for updating user info
									std::thread(getUserInfoAsync).detach();
									globals::menuTab = 0;
									globals::loggedIn = true;
									globals::active = false;
								}
								else {
									MessageBoxA(NULL, "Failed to get user info.", "Error", MB_OK | MB_ICONERROR);
								}
								
							}
							else {
								MessageBoxA(NULL, "Invalid credentials or HWID.", "Error", MB_OK | MB_ICONERROR);
							}
						}
					}



					ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 25));



					if (ImGui::Button("Register", ImVec2(globals::window_size.x / 2, 30.f)))
					{
						globals::menuTab = 4;
						
					}


					break;

				}
				case 4:
				{
					ImGui::Spacing();
					ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("Register For An Account").x) / 2);
					ImGui::Text("Register For An Account");
					ImGui::Spacing();
					ImGui::PushItemWidth(globals::window_size.x / 2);
					{
						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 9));
						ImGui::Text("Username");

						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 11));
						ImGui::InputText("##Username", globals::inputusername, sizeof(globals::inputusername));
					}

					{
						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 15));
						ImGui::Text("Email");

						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 17));
						ImGui::InputText("##Email", globals::inputmail, sizeof(globals::inputmail));
					}

					
					{
						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 21));
						ImGui::Text("Password");

						ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 23));
						ImGui::InputText("##Password", globals::inputpassword, sizeof(globals::inputpassword), ImGuiInputTextFlags_Password);
					}
					ImGui::PopItemWidth();

					ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 27));
					if (ImGui::Button("Register", ImVec2(globals::window_size.x / 2, 30.f)))
					{
						if (globals::api.signup(globals::inputusername, globals::inputpassword, globals::inputmail, globals::hwid)) {
							MessageBoxA(NULL, "Account created successfully.", "Success", MB_OK | MB_ICONINFORMATION);
							globals::menuTab = 3;
						}
						else {
							MessageBoxA(NULL, "Account creation failed.", "Error", MB_OK | MB_ICONERROR);
						}
					}
					ImGui::Spacing();
					ImGui::SetCursorPos(ImVec2(globals::padding * 2, globals::padding * 31));
					if (ImGui::Selectable("Already have an account? Login.", false, ImGuiSelectableFlags_None)) {
						globals::menuTab = 3;
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