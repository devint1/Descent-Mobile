//
//  FONTOGLES.h
//  2D
//
//  Created by Devin Tuchsen on 11/22/15.
//  Copyright © 2015 Devin Tuchsen. All rights reserved.
//

#ifndef FONTOGLES_h
#define FONTOGLES_h

#ifdef OGLES
void gr_scale_string_ogles(int x, int y, fix scale_x, fix scale_y, char * s);
#endif

#endif /* FONTOGLES_h */
