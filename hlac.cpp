void HLACExtractClass::featureExtract(IplImage* input_image, CvMat* feature_mat) const
{
	
	int h = input_image->height - 1;
	int w = input_image->width - 1;
	int wideStep = input_image->widthStep;

	int feature_num = feature_mat->rows;

	for(int i = 0; i < feature_num; i++)
		cvmSet(feature_mat, i, 0, 0.0);

	double arrayHLAC[25];
	for(int i = 0; i < 25; ++i)
		arrayHLAC[i] = 0.0;

	// 特徴抽出
	for(int iy = 1; iy < h; iy++){
		for(int ix = 1; ix < w; ix++){
			uchar p5 = (uchar)input_image->imageData[wideStep*iy + ix];
			if(p5 != 0)
			{
				arrayHLAC[0]++;
				uchar p1 = (uchar)input_image->imageData[wideStep*(iy-1) + (ix-1)];
				uchar p2 = (uchar)input_image->imageData[wideStep*(iy-1) + ix    ];
				uchar p3 = (uchar)input_image->imageData[wideStep*(iy-1) + (ix+1)];
				uchar p4 = (uchar)input_image->imageData[wideStep*iy     + (ix-1)];

				uchar p6 = (uchar)input_image->imageData[wideStep*iy	 + (ix+1)];
				uchar p7 = (uchar)input_image->imageData[wideStep*(iy+1) + (ix+1)];
				uchar p8 = (uchar)input_image->imageData[wideStep*(iy+1) + ix    ];
				uchar p9 = (uchar)input_image->imageData[wideStep*(iy+1) + (ix+1)];


				if(p1 != 0){	arrayHLAC[1]++;
					if(p8 != 0)	arrayHLAC[13]++;
					if(p3 != 0)	arrayHLAC[21]++;
					if(p7 != 0)	arrayHLAC[22]++;
				}
				if(p2 != 0){	arrayHLAC[2]++;
					if(p8 != 0)	arrayHLAC[7]++;
					if(p7 != 0)	arrayHLAC[11]++;
					if(p9 != 0)	arrayHLAC[12]++;
					if(p6 != 0)	arrayHLAC[17]++;
				}
				if(p3 != 0){	arrayHLAC[3]++;
					if(p7 != 0)	arrayHLAC[6]++;
					if(p4 != 0) arrayHLAC[9]++;
					if(p8 != 0) arrayHLAC[14]++;
				}
				if(p4 != 0){	arrayHLAC[4]++;
					if(p6 != 0)	arrayHLAC[5]++;
					if(p9 != 0)	arrayHLAC[10]++;
					if(p2 != 0)	arrayHLAC[18]++;
					if(p8 != 0)	arrayHLAC[19]++;
				}
				if(p6 != 0){
					if(p7 != 0)	arrayHLAC[15]++;
					if(p1 != 0)	arrayHLAC[16]++;
					if(p8 != 0)	arrayHLAC[20]++;
				}
				if(p9 != 0){
					if(p1 != 0)	arrayHLAC[8]++;
					if(p7 != 0)	arrayHLAC[23]++;
					if(p3 != 0)	arrayHLAC[24]++;
				}
			}
		}
	}
	
	for(int i = 0; i < feature_num && i < 25; ++i)
		cvmSet(feature_mat, i, 0, arrayHLAC[i]);
	return;

}
