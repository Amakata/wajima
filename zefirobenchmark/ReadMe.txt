========================================================================
    WIN32 アプリケーション : zefirobenchmark プロジェクトの概要
========================================================================
■アプリケーションの概要
　◇zefirobenchmarkはDirectX8.1のDirectGraphics用ベンチマークソフトです。
　◇800x600x32のスクリーンでの[fps]、[texel/s]、[tri/s]を測定してファイルに出力します。

■バージョン
 1.2

■操作
　◇ベンチマークは、メニュから実行することができます。
　◇ベンチマークは、ESCキーで中断することができます。

■ベンチマークの種類
◇ウィンドウモード・不透明テクスチャ
◇フルスクリーンモード・不透明テクスチャ
◇ウィンドウモード・半透明テクスチャ
◇フルスクリーンモード・半透明テクスチャ

■ベンチ時間
　テクスチャサイズの種類×テクスチャ数の種類××約5[s]

■テクスチャサイズ
　16x16、32x32、64x64、128x128、256x256の正方テクスチャ
　◇テクスチャファイル名
　　不透明 16.png、32.png、64.png、128.png、256.png
　　半透明 16a.png、32a.png、64a.png、128a.png、256a.png

■テクスチャ数
　◇不透明 1000,2500,5000,10000,20000,40000
　◇半透明 100,250,500,1000,2000,4000

■結果
　◇ベンチマーク zefirobenchmarkoutput.txtに出力されます。
　◇エラーログ error_log.txtに出力されます。
　◇レンダリング状態 state.txtに出力されます。
■注意
　テクスチャファイルがない場合・DirectX8.1がインストールしてない場合・デバイスが描画に対応してない場合の
動作は保障しておりません。気をつけてご利用ください。

■バージョン履歴
◇1.2
　カリングをOFFにした。
　頂点の色情報を反映しないようにした。
　可能な限り、24bit以下のデバイスでも測定できるようにした。
　リファレンスドライバでハードウェア頂点処理のデバイスを作成しないようにした。
　テクスチャーの合成オペレーションを明示的に設定した。（第１テクスチャーの色のみ利用）
　テクスチャーのメモリ領域をデフォルトからマネージに切り替えた。
　デフォルトのレンダリング状態を出力するようにした。
◇1.1
　ESCキーでベンチマークの途中で処理を抜けられるようにした。
　ベンチマークの終了をメッセージボックスで知らせるようにした。
　error_log.txtにDirectX関連のエラーログを出力するようにした。
　可能な限りD3Dデバイスを作成するようにした。
　可能な限り頂点バッファのロックをするようにした。
　ウィンドウモードで24bitモード以外でベンチマークを取ろうとした場合は、24bitモードに変更するよう表示するようにした。
◇1.0
　初期バージョン

■ベンチマークの見本
DellのDimension4400で測定しました。
Pentium４ 1.7GHz Mem 512MB
----以下見本-----
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x1000 [Sprites] 106.383 [fps] 27.234 [Mtexel/s] 212766 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x2500 [Sprites] 106.383 [fps] 68.0851 [Mtexel/s] 531915 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x5000 [Sprites] 53.1915 [fps] 68.0851 [Mtexel/s] 531915 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x10000 [Sprites] 29.0698 [fps] 74.4186 [Mtexel/s] 581395 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x20000 [Sprites] 15.2439 [fps] 78.0488 [Mtexel/s] 609756 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 16x16x40000 [Sprites] 14.5773 [fps] 149.271 [Mtexel/s] 1.16618e+006 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x1000 [Sprites] 63.2911 [fps] 64.8101 [Mtexel/s] 126582 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x2500 [Sprites] 35.7143 [fps] 91.4286 [Mtexel/s] 178571 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x5000 [Sprites] 22.8311 [fps] 116.895 [Mtexel/s] 228311 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x10000 [Sprites] 12.7877 [fps] 130.946 [Mtexel/s] 255754 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x20000 [Sprites] 8 [fps] 163.84 [Mtexel/s] 320000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 32x32x40000 [Sprites] 8.8968 [fps] 364.413 [Mtexel/s] 711744 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x1000 [Sprites] 32.0513 [fps] 131.282 [Mtexel/s] 64102.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x2500 [Sprites] 14.5349 [fps] 148.837 [Mtexel/s] 72674.4 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x5000 [Sprites] 8 [fps] 163.84 [Mtexel/s] 80000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x10000 [Sprites] 4.2123 [fps] 172.536 [Mtexel/s] 84246 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x20000 [Sprites] 3.72024 [fps] 304.762 [Mtexel/s] 148810 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 64x64x40000 [Sprites] 3.47947 [fps] 570.077 [Mtexel/s] 278358 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x1000 [Sprites] 11.4416 [fps] 187.46 [Mtexel/s] 22883.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x2500 [Sprites] 4.84966 [fps] 198.642 [Mtexel/s] 24248.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x5000 [Sprites] 2.5 [fps] 204.8 [Mtexel/s] 25000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x10000 [Sprites] 1.27486 [fps] 208.873 [Mtexel/s] 25497.2 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x20000 [Sprites] 1.15527 [fps] 378.558 [Mtexel/s] 46210.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 128x128x40000 [Sprites] 1.11111 [fps] 728.178 [Mtexel/s] 88888.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x1000 [Sprites] 4.10172 [fps] 268.81 [Mtexel/s] 8203.45 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x2500 [Sprites] 1.6756 [fps] 274.531 [Mtexel/s] 8378.02 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x5000 [Sprites] 0.853388 [fps] 279.638 [Mtexel/s] 8533.88 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x10000 [Sprites] 0.535963 [fps] 351.249 [Mtexel/s] 10719.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x20000 [Sprites] 0.488568 [fps] 640.375 [Mtexel/s] 19542.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （不透明） 256x256x40000 [Sprites] 0.482625 [fps] 1265.17 [Mtexel/s] 38610 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x1000 [Sprites] 53.1915 [fps] 13.617 [Mtexel/s] 106383 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x2500 [Sprites] 64.1026 [fps] 41.0256 [Mtexel/s] 320513 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x5000 [Sprites] 53.7634 [fps] 68.8172 [Mtexel/s] 537634 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x10000 [Sprites] 29.0698 [fps] 74.4186 [Mtexel/s] 581395 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x20000 [Sprites] 16.835 [fps] 86.1953 [Mtexel/s] 673401 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 16x16x40000 [Sprites] 17.7305 [fps] 181.56 [Mtexel/s] 1.41844e+006 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x1000 [Sprites] 45.8716 [fps] 46.9725 [Mtexel/s] 91743.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x2500 [Sprites] 32.0513 [fps] 82.0513 [Mtexel/s] 160256 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x5000 [Sprites] 24.6305 [fps] 126.108 [Mtexel/s] 246305 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x10000 [Sprites] 11.4155 [fps] 116.895 [Mtexel/s] 228311 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x20000 [Sprites] 11.8483 [fps] 242.654 [Mtexel/s] 473934 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 32x32x40000 [Sprites] 8.19672 [fps] 335.738 [Mtexel/s] 655738 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x1000 [Sprites] 29.0698 [fps] 119.07 [Mtexel/s] 58139.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x2500 [Sprites] 13.3333 [fps] 136.533 [Mtexel/s] 66666.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x5000 [Sprites] 8.41751 [fps] 172.391 [Mtexel/s] 84175.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x10000 [Sprites] 4.70367 [fps] 192.662 [Mtexel/s] 94073.4 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x20000 [Sprites] 3.95257 [fps] 323.794 [Mtexel/s] 158103 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 64x64x40000 [Sprites] 3.90016 [fps] 639.002 [Mtexel/s] 312012 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x1000 [Sprites] 12.3153 [fps] 201.773 [Mtexel/s] 24630.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x2500 [Sprites] 5.24109 [fps] 214.675 [Mtexel/s] 26205.4 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x5000 [Sprites] 2.6441 [fps] 216.605 [Mtexel/s] 26441 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x10000 [Sprites] 1.40331 [fps] 229.919 [Mtexel/s] 28066.2 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x20000 [Sprites] 1.29032 [fps] 422.813 [Mtexel/s] 51612.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 128x128x40000 [Sprites] 1.25 [fps] 819.2 [Mtexel/s] 100000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x1000 [Sprites] 4.63822 [fps] 303.97 [Mtexel/s] 9276.44 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x2500 [Sprites] 1.82882 [fps] 299.634 [Mtexel/s] 9144.11 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x5000 [Sprites] 0.949487 [fps] 311.128 [Mtexel/s] 9494.87 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x10000 [Sprites] 0.595877 [fps] 390.514 [Mtexel/s] 11917.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x20000 [Sprites] 0.545137 [fps] 714.523 [Mtexel/s] 21805.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （不透明） 256x256x40000 [Sprites] 0.536884 [fps] 1407.41 [Mtexel/s] 42950.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x100 [Sprites] 161.29 [fps] 4.12903 [Mtexel/s] 32258.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x250 [Sprites] 80.6452 [fps] 5.16129 [Mtexel/s] 40322.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x500 [Sprites] 161.29 [fps] 20.6452 [Mtexel/s] 161290 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x1000 [Sprites] 156.25 [fps] 40 [Mtexel/s] 312500 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x2000 [Sprites] 53.1915 [fps] 27.234 [Mtexel/s] 212766 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 16x16x4000 [Sprites] 53.1915 [fps] 54.4681 [Mtexel/s] 425532 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x100 [Sprites] 161.29 [fps] 16.5161 [Mtexel/s] 32258.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x250 [Sprites] 156.25 [fps] 40 [Mtexel/s] 78125 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x500 [Sprites] 106.383 [fps] 54.4681 [Mtexel/s] 106383 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x1000 [Sprites] 64.1026 [fps] 65.641 [Mtexel/s] 128205 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x2000 [Sprites] 24.5098 [fps] 50.1961 [Mtexel/s] 98039.2 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 32x32x4000 [Sprites] 20 [fps] 81.92 [Mtexel/s] 160000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x100 [Sprites] 106.383 [fps] 43.5745 [Mtexel/s] 21276.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x250 [Sprites] 64.1026 [fps] 65.641 [Mtexel/s] 32051.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x500 [Sprites] 45.4545 [fps] 93.0909 [Mtexel/s] 45454.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x1000 [Sprites] 22.9358 [fps] 93.945 [Mtexel/s] 45871.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x2000 [Sprites] 11.8765 [fps] 97.2922 [Mtexel/s] 47505.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 64x64x4000 [Sprites] 6.15764 [fps] 100.887 [Mtexel/s] 49261.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x100 [Sprites] 64.1026 [fps] 105.026 [Mtexel/s] 12820.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x250 [Sprites] 26.738 [fps] 109.519 [Mtexel/s] 13369 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x500 [Sprites] 14.5773 [fps] 119.417 [Mtexel/s] 14577.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x1000 [Sprites] 7.62195 [fps] 124.878 [Mtexel/s] 15243.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x2000 [Sprites] 3.67918 [fps] 120.559 [Mtexel/s] 14716.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 128x128x4000 [Sprites] 1.91644 [fps] 125.596 [Mtexel/s] 15331.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x100 [Sprites] 22.8311 [fps] 149.626 [Mtexel/s] 4566.21 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x250 [Sprites] 8 [fps] 131.072 [Mtexel/s] 4000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x500 [Sprites] 5 [fps] 163.84 [Mtexel/s] 5000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x1000 [Sprites] 2.52016 [fps] 165.161 [Mtexel/s] 5040.32 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x2000 [Sprites] 1.24502 [fps] 163.187 [Mtexel/s] 4980.08 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （ウィンドウモード） （半透明） 256x256x4000 [Sprites] 0.792142 [fps] 207.655 [Mtexel/s] 6337.14 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x100 [Sprites] 53.1915 [fps] 1.3617 [Mtexel/s] 10638.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x250 [Sprites] 64.1026 [fps] 4.10256 [Mtexel/s] 32051.3 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x500 [Sprites] 64.1026 [fps] 8.20513 [Mtexel/s] 64102.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x1000 [Sprites] 64.1026 [fps] 16.4103 [Mtexel/s] 128205 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x2000 [Sprites] 40 [fps] 20.48 [Mtexel/s] 160000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 16x16x4000 [Sprites] 64.1026 [fps] 65.641 [Mtexel/s] 512821 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x100 [Sprites] 35.461 [fps] 3.63121 [Mtexel/s] 7092.2 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x250 [Sprites] 53.1915 [fps] 13.617 [Mtexel/s] 26595.7 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x500 [Sprites] 45.4545 [fps] 23.2727 [Mtexel/s] 45454.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x1000 [Sprites] 64.1026 [fps] 65.641 [Mtexel/s] 128205 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x2000 [Sprites] 31.8471 [fps] 65.2229 [Mtexel/s] 127389 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 32x32x4000 [Sprites] 18.797 [fps] 76.9925 [Mtexel/s] 150376 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x100 [Sprites] 64.1026 [fps] 26.2564 [Mtexel/s] 12820.5 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x250 [Sprites] 32.0513 [fps] 32.8205 [Mtexel/s] 16025.6 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x500 [Sprites] 29.0698 [fps] 59.5349 [Mtexel/s] 29069.8 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x1000 [Sprites] 20 [fps] 81.92 [Mtexel/s] 40000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x2000 [Sprites] 12.285 [fps] 100.639 [Mtexel/s] 49140.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 64x64x4000 [Sprites] 6.80272 [fps] 111.456 [Mtexel/s] 54421.8 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x100 [Sprites] 45.8716 [fps] 75.156 [Mtexel/s] 9174.31 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x250 [Sprites] 26.5957 [fps] 108.936 [Mtexel/s] 13297.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x500 [Sprites] 15.2439 [fps] 124.878 [Mtexel/s] 15243.9 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x1000 [Sprites] 7.8125 [fps] 128 [Mtexel/s] 15625 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x2000 [Sprites] 4.26621 [fps] 139.795 [Mtexel/s] 17064.8 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 128x128x4000 [Sprites] 2.14777 [fps] 140.756 [Mtexel/s] 17182.1 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x100 [Sprites] 20 [fps] 131.072 [Mtexel/s] 4000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x250 [Sprites] 10 [fps] 163.84 [Mtexel/s] 5000 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x500 [Sprites] 5.33618 [fps] 174.856 [Mtexel/s] 5336.18 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x1000 [Sprites] 2.83126 [fps] 185.549 [Mtexel/s] 5662.51 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x2000 [Sprites] 1.43472 [fps] 188.052 [Mtexel/s] 5738.88 [tri/s]
nv4_disp.dll NVIDIA GeForce2 MX/MX 400                           （フルスクリーンモード） （半透明） 256x256x4000 [Sprites] 0.884017 [fps] 231.74 [Mtexel/s] 7072.14 [tri/s]
