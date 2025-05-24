import type { Metadata } from "next";
import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";

const geistSans = Geist({
  variable: "--font-geist-sans",
  subsets: ["latin"],
});

const geistMono = Geist_Mono({
  variable: "--font-geist-mono",
  subsets: ["latin"],
});

export const metadata: Metadata = {
  title: "Página poggers",
  description: "Aula 04 projeto next pog",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="pt-br">
      <body
        className={`${geistSans.variable} ${geistMono.variable} antialiased`}
      >

        <header className="h-[80px]">Header</header>
  
        <main className="h-screen bg-[#121212]">
          {children}
        </main>


        <footer className="h-[150px] bg-[#242424]">
          aasdasd
        </footer>
      </body>
    </html>
  );
}
