#include "ResizeKernels.h"
L1_CL_MEM AT_L1_POINTER Resize_L1_Memory;
L2_MEM AT_L2_POINTER Resize_L2_Memory;
void ResizeImage(
		unsigned char * In,
		unsigned char * Out)

{
	/* Shared L1: 39288 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	KerResizeBilinear_ArgT S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last, D0Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _N_In, _Off_In;
	unsigned int _SN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: 1][Tile0 Dim: 6]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 19481 [D0, [0 x 19481, 19481]][Tile0, 6:[161x24, 4:161x24, 161x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 19481, 19481]][Tile0, 6:[161x24, 4:161x24, 161x1], 1]
		Tile0: [0, 3864, 3864], Tile1: [3864, 3864, 3864], Tile2; [7728, 3864, 3864]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 6 logical tiles, 6 physical tiles
			Total Size: 77924 [D0, [0 x 77924, 77924]][Tile0, 6:[322x49, 4:322x49, 322x3], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 77924, 77924]][Tile0, 6:[322x49, 4:322x49, 322x3], 1]
		Tile0: [0, 15778, 15778], Tile1: [15134, 15778, 15778], Tile2; [30590, 15778, 15778]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Win = (unsigned int) (322);
	KerArg0->Hin = (unsigned int) (242);
	KerArg0->Wout = (unsigned int) (161);
	KerArg0->Hout = (unsigned int) (121);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=3864;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) Resize_L1_Memory+0+0), 15778, 0, &DmaR_Evt1);
	_N_In=0;
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1;
		for (T0Ind=0; T0Ind<6; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==5), T0Ind_NextLast = ((T0Ind+1)==5);
			/*================================= Prepare Tiles ===================================*/
			_SN_In = 0;
			if (!(T0Ind_Last)) {
				_N_In = _N_In + 0; _Off_In = (((130530*((T0Ind)+1)*24)>>16)*322); _SN_In = ((T0Ind_NextLast)?966:15778); 
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In+_Off_In), ((AT_L2_INT_ADDR_TYPE) Resize_L1_Memory+0+15780*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg0->In = (unsigned char * __restrict__) (Resize_L1_Memory+0+15780*((T0Ind_Total)%2));
			KerArg0->Out = (unsigned char * __restrict__) (Resize_L1_Memory+31560+3864*((T0Ind_Total)%2));
			KerArg0->HTileOut = (unsigned int) (T0Ind_Last?1:24);
			KerArg0->FirstLineIndex = (unsigned int) ((130530*(T0Ind)*24)>>16);
			AT_FORK(gap_ncore(), (void *) KerResizeBilinear, (void *) KerArg0);
			__CALL(KerResizeBilinear, KerArg0);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) Resize_L1_Memory+31560+3864*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (3864); _SC_Out = ((T0Ind_NextLast)?161:3864); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
