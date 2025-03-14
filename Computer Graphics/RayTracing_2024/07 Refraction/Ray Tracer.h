#pragma once

#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>

namespace RayTracer 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	struct intersections
	{
		float distance;
		int   indice;
	} intersection;

	public ref class RayTracer : public System::Windows::Forms::Form
	{
		public:
			RayTracer(void)
			{
				InitializeComponent();
			}

		protected:
			~RayTracer()
			{
				if (components)
				{
					delete components;
				}
			}

		private: System::Windows::Forms::PictureBox^  surfacePictureBox;
		protected:
		private: System::Windows::Forms::Button^  Render;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::TextBox^  timeBox;


		private:
			System::ComponentModel::Container ^components;

		public:
			Bitmap myBitmap = Bitmap::FromFile("..\\Textures\\zemin.jpg");

		#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->surfacePictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->Render = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timeBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->surfacePictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// surfacePictureBox
			// 
			this->surfacePictureBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->surfacePictureBox->Location = System::Drawing::Point(12, 12);
			this->surfacePictureBox->Name = L"surfacePictureBox";
			this->surfacePictureBox->Size = System::Drawing::Size(800, 450);
			this->surfacePictureBox->TabIndex = 0;
			this->surfacePictureBox->TabStop = false;
			// 
			// Render
			// 
			this->Render->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->Render->Location = System::Drawing::Point(376, 475);
			this->Render->Name = L"Render";
			this->Render->Size = System::Drawing::Size(79, 24);
			this->Render->TabIndex = 1;
			this->Render->Text = L"Render";
			this->Render->UseVisualStyleBackColor = true;
			this->Render->Click += gcnew System::EventHandler(this, &RayTracer::Render_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label1->Location = System::Drawing::Point(604, 479);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(136, 16);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Rendering Time (sn) :";
			// 
			// timeBox
			// 
			this->timeBox->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->timeBox->Location = System::Drawing::Point(742, 474);
			this->timeBox->Name = L"timeBox";
			this->timeBox->Size = System::Drawing::Size(68, 26);
			this->timeBox->TabIndex = 3;
			this->timeBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// RayTracer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(823, 513);
			this->Controls->Add(this->timeBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Render);
			this->Controls->Add(this->surfacePictureBox);
			this->Name = L"RayTracer";
			this->Text = L"RayTracer : Refraction";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->surfacePictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
		#pragma endregion
		
		#pragma region ShadeDiffuse ShadeSpecular ShadingModel

		Color ShadeDiffuse(Shape* S, Vertex iPoint)
		{
			Vertex light = Vertex(0, 100, 100);

			Vertex toLight = (light - iPoint).Normalize();
			Vertex normal = S->NormalAt(iPoint).Normalize();
			Color c = S->ShapeColor;

			float diffuseKatsayi = normal * toLight;
			if (diffuseKatsayi < 0.0f) return Color::Black;

			float r = 0, g = 0, b = 0;
			r += diffuseKatsayi * c.R;
			g += diffuseKatsayi * c.G;
			b += diffuseKatsayi * c.B;

			r = r > 255 ? 255 : r; r = r < 0 ? 0 : r;
			g = g > 255 ? 255 : g; g = g < 0 ? 0 : g;
			b = b > 255 ? 255 : b; b = b < 0 ? 0 : b;

			return Color::FromArgb((int)r, (int)g, (int)b);
		}

		Color ShadeSpecular(Shape* S, Vertex iPoint, Vertex camera)
		{
			Vertex light = Vertex(0, 100, 100);

			Vertex fromLight = (iPoint - light).Normalize();
			Vertex normal = S->NormalAt(iPoint).Normalize();
			Vertex toCamera = (camera - iPoint).Normalize();

			Color Lamba = Color::White;
			Vertex reflected = (fromLight - 2 * (normal * fromLight) * normal).Normalize();
			float dotProduct = reflected * toCamera;
			if (dotProduct < 0.0f) return Color::Black;

			float specularKatsayi = (float)Math::Pow((double)(dotProduct), (double)8);

			float r = 0, g = 0, b = 0;
			r += specularKatsayi * Lamba.R;
			g += specularKatsayi * Lamba.G;
			b += specularKatsayi * Lamba.B;

			r = r > 255 ? 255 : r; r = r < 0 ? 0 : r;
			g = g > 255 ? 255 : g; g = g < 0 ? 0 : g;
			b = b > 255 ? 255 : b; b = b < 0 ? 0 : b;

			return Color::FromArgb((int)r, (int)g, (int)b);
		}

		Color ShadingModel(Shape* S, Color diffuseColor, Color specularColor, Color reflectedColor, Color transmittedColor, Color refractedColor, float amb, float dif, float spec, float refl, float trans, float refrac)
		{
			Color ambientcolor = S->ShapeColor;

			int r = Math::Min(255, (int)(amb * ambientcolor.R + dif * diffuseColor.R + spec * specularColor.R + refl * reflectedColor.R + trans * transmittedColor.R + refrac * refractedColor.R));
			int g = Math::Min(255, (int)(amb * ambientcolor.G + dif * diffuseColor.G + spec * specularColor.G + refl * reflectedColor.G + trans * transmittedColor.G + refrac * refractedColor.G));
			int b = Math::Min(255, (int)(amb * ambientcolor.B + dif * diffuseColor.B + spec * specularColor.B + refl * reflectedColor.B + trans * transmittedColor.B + refrac * refractedColor.B));

			return Color::FromArgb(r, g, b);
		}

		#pragma endregion

		#pragma region Calculate Reflection Transmission Refraction

		Vertex CalculateReflection(Shape* S, Vertex iPoint, Vertex Rd)
		{
			Vertex normal = S->NormalAt(iPoint).Normalize();
			return (Rd - 2 * (normal * Rd) * normal).Normalize();
		}

		Vertex CalculateTransmission(Shape* S, Vertex iPoint, Vertex Rd)
		{
			return Rd;
		}

		Vertex CalculateRefraction(Shape* S, Vertex iPoint, Vertex Rd, float n1, float n2)
		{
			// Real-Time Rendering (2nd Edition) page : 246
			//
			//  Rd  \           Rd : gelen ���n�n do�rultusu
			//       \			n1 : 1. ortam�n k�r�lma indisi
			// _______\__________ 
			//        | 
			//        |			n2 : 2. ortam�n k�r�lma indisi
			//        | 
			//        t			t  : refracted direction
			//
			// r = n1 / n2
			// w = -(Rd*n)r
			// k = sqrt(1+(w-r)(w+r))
			// t = r*Rd + (w-k)n       (refracted direction)

			Vertex normal = S->NormalAt(iPoint).Normalize();
			float       r = n1 / n2;
			float       w = -(Rd * normal) * r;
			float       k = (float)Math::Sqrt((double)(1 + (w - r) * (w + r)));
			return      (r * Rd + normal * (w-k)).Normalize(); // t
		}

		#pragma endregion

		#pragma region Texture Mapping

		void TextureMapping(Vertex Ro, Vertex Rd, Shape* S)
		{
			switch (S->Tex)
			{
				int x, y;

				case 1:
				{
					float t = S->Intersect(Ro, Rd);
					Vertex iPoint = Ro + t * Rd;

					float u = (iPoint.X - S->V0.X) / (S->V1.X - S->V0.X);
					float v = (iPoint.Z - S->V0.Z) / (S->V2.Z - S->V0.Z);

					x = (int)(u * 800);
					y = (int)(v * 800);

					x = x > 799 ? 799 : x; x = x < 0 ? 0 : x;
					y = y > 799 ? 799 : y; y = y < 0 ? 0 : y;

					S->ShapeColor = myBitmap.GetPixel(x, y);
				}
				break;

				case 2:
				{
					float t = S->Intersect(Ro, Rd);
					Vertex iPoint = Ro + t * Rd;

					float u = (iPoint.X - S->V0.X) / (S->V1.X - S->V0.X);
					float v = (iPoint.Z - S->V0.Z) / (S->V2.Z - S->V0.Z);

					x = (int)((1-u) * 800);
					y = (int)((1-v) * 800);

					x = x > 799 ? 799 : x; x = x < 0 ? 0 : x;
					y = y > 799 ? 799 : y; y = y < 0 ? 0 : y;

					S->ShapeColor = myBitmap.GetPixel(x, y);
				}
				break;
			}
		}
		#pragma endregion

		Color TraceRay(Vertex Ro, Vertex Rd, Shape* Shapes[], Vertex camera, int depth, Shape* prevShape)
		{
			if (depth > 4)
			{
				return prevShape->ShapeColor;
				//return Color::Black;
			}

			vector<intersections> Intersections;

			for (int i = 0; i < 30; i++)
			{
				float t = Shapes[i]->Intersect(Ro, Rd);

				if (t > 0.1F)						// 0.1 is a bias value for avoiding self intersection
				{
					intersection.distance = t;
					intersection.indice   = i;

					Intersections.push_back(intersection);
				}
			}

			if (Intersections.size() > 0)
			{
				float min_distance = FLT_MAX;
				int   min_indis = -1;

				for (int i = 0; i < Intersections.size(); i++)
				{
					if (Intersections[i].distance < min_distance)
					{
						min_indis    = Intersections[i].indice;
						min_distance = Intersections[i].distance;
					}
				}

				Vertex iPoint = Ro + min_distance * Rd;			
				Shape* S      = Shapes[min_indis];

				TextureMapping(Ro, Rd, S);

				Color reflectedColor;
				if (S->Refl != 0.0F)
				{
					Vertex reflectedDirection = CalculateReflection(S, iPoint, Rd);
					reflectedColor = TraceRay(iPoint, reflectedDirection, Shapes, camera, depth + 1, S);
				}

				Color transmittedColor;
				if (S->Trans != 0.0F)
				{
					Vertex transmittedDirection = CalculateTransmission(S, iPoint, Rd);
					transmittedColor = TraceRay(iPoint, transmittedDirection, Shapes, camera, depth + 1, S);
				}

				Color refractedColor;
				if (S->Refrac != 0.0F)
				{
					Vertex refractedDirection = CalculateRefraction(S, iPoint, Rd, 1.0F, 1.33F);
					refractedColor = TraceRay(iPoint, refractedDirection, Shapes, camera, depth + 1, S);
				}

				Color diffuseColor  = ShadeDiffuse(S, iPoint);
				Color specularColor = ShadeSpecular(S, iPoint, camera);

				return ShadingModel(S, diffuseColor, specularColor, reflectedColor, transmittedColor, refractedColor, S->Ambient, S->Dif, S->Spec, S->Refl, S->Trans, S->Refrac);
			}

			return Color::Black;
		}

		private: System::Void Render_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			DateTime startTime; 
			startTime = startTime.Now;

			Bitmap^ surface = gcnew Bitmap(800, 450);
			surfacePictureBox->Image = surface;

			Triangle T1(Vertex(200, -50, -50), Vertex(-200, -50, -50), Vertex(200, -50, 350), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 2); // Zemin
			Triangle T2(Vertex(-200, -50, 350), Vertex(200, -50, 350), Vertex(-200, -50, -50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 1);

			Triangle T3(Vertex(100, 0, 50), Vertex(100, -50, 50), Vertex(-100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T4(Vertex(-100, 0, 50), Vertex(100, 0, 50), Vertex(-100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T5(Vertex(100, -50, 250), Vertex(100, 0, 250), Vertex(-100, -50, 250), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T6(Vertex(100, 0, 250), Vertex(-100, 0, 250), Vertex(-100, -50, 250), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T7(Vertex(90, -50, 60), Vertex(90, 0, 60), Vertex(-90, -50, 60), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T8(Vertex(90, 0, 60), Vertex(-90, 0, 60), Vertex(-90, -50, 60), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T9(Vertex(90, 0, 240), Vertex(90, -50, 240), Vertex(-90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T10(Vertex(-90, 0, 240), Vertex(90, 0, 240), Vertex(-90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T11(Vertex(100, 0, 250), Vertex(100, -50, 250), Vertex(100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T12(Vertex(100, 0, 50), Vertex(100, 0, 250), Vertex(100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T13(Vertex(-100, -50, 250), Vertex(-100, 0, 250), Vertex(-100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T14(Vertex(-100, 0, 250), Vertex(-100, 0, 50), Vertex(-100, -50, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T15(Vertex(90, 0, 60), Vertex(90, -50, 60), Vertex(90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T16(Vertex(90, 0, 240), Vertex(90, 0, 60), Vertex(90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T17(Vertex(-90, -50, 60), Vertex(-90, 0, 60), Vertex(-90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T18(Vertex(-90, 0, 60), Vertex(-90, 0, 240), Vertex(-90, -50, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T19(Vertex(100, 0, 250), Vertex(100, 0, 50), Vertex(90, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T20(Vertex(90, 0, 250), Vertex(100, 0, 250), Vertex(90, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T21(Vertex(-90, 0, 250), Vertex(-90, 0, 50), Vertex(-100, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T22(Vertex(-100, 0, 250), Vertex(-90, 0, 250), Vertex(-100, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T23(Vertex(90, 0, 250), Vertex(90, 0, 240), Vertex(-90, 0, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T24(Vertex(-90, 0, 250), Vertex(90, 0, 250), Vertex(-90, 0, 240), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T25(Vertex(90, 0, 60), Vertex(90, 0, 50), Vertex(-90, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);
			Triangle T26(Vertex(-90, 0, 60), Vertex(90, 0, 60), Vertex(-90, 0, 50), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::White, 0);

			Triangle T27(Vertex(89, -5, 239), Vertex(89, -5, 61), Vertex(-89, -5, 61), 0.1, 0.2, 0.0, 0.0, 0.0, 0.7, Color::White, 0);  //  SU
			Triangle T28(Vertex(-89, -5, 239), Vertex(89, -5, 239), Vertex(-89, -5, 61), 0.1, 0.2, 0.0, 0.0, 0.0, 0.7, Color::White, 0);

			Triangle T29(Vertex(70, 50, 90), Vertex(0, -50, 90), Vertex(0, -50, 100), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::Red, 0);  // �UBUK
			Triangle T30(Vertex(70, 50, 100), Vertex(70, 50, 90), Vertex(0, -50, 100), 0.3, 0.7, 0.0, 0.0, 0.0, 0.0, Color::Red, 0);

			Shape* Shapes[30] = { &T1, &T2, &T3, &T4, &T5, &T6, &T7, &T8, &T9, &T10, &T11, &T12, &T13, &T14, &T15,
								  &T16, &T17, &T18, &T19, &T20, &T21, &T22, &T23, &T24, &T25, &T26, &T27, &T28, &T29, &T30};

			// x-ekseninde 45 derece d�nd�r
			// �nceki konumlar : P0(-8, 100, 0), P1(8, 100, 0), P2(8, 91, 0), P3(-8, 91, 0), 
			Vertex P0(-8, 98.68,  3.18);
			Vertex P1( 8, 98.68,  3.18);
			Vertex P2( 8, 89.68, -3.18);
			Vertex P3(-8, 89.68, -3.17);

			Vertex norm = (P1 - P0).CrossProduct(P2 - P1);
			norm.Normalize();

			Vertex camera = (P0 + P2) / 2 + 10 * norm;

			Vertex Px = (P1 - P0) / 799.0F;
			Vertex Py = (P3 - P0) / 449.0F;

			for (int y = 0; y < 450; y++)
			{
				for (int x = 0; x < 800; x++)
				{
					//Vertex pixel = Vertex(8 * x / 799.0F - 4, 3 - y * 6 / 599.0F, 5);
					Vertex pixel = P0 + Px * (float)x + Py * (float)y;
					Vertex Rd    = (pixel - camera).Normalize();
					Color c      = TraceRay(camera, Rd, Shapes, camera, 0, NULL);
					surface->SetPixel(x, y, c);
				}
				surfacePictureBox->Refresh();
			}

			DateTime endTime;
			endTime = endTime.Now;
			TimeSpan deltaTime = endTime - startTime;
			timeBox->Text = (Math::Round(100 * deltaTime.TotalSeconds) / 100.0F).ToString();

			DateTime date;
			String^ filename = date.Now.Year.ToString() + date.Now.Month.ToString() + date.Now.Day.ToString() +
				date.Now.Hour.ToString() + date.Now.Minute.ToString() + date.Now.Second.ToString() + ".jpg";
			surface->Save("image/" + filename);
		}
	};
}