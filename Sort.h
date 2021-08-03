/********************************************************************
 * This class contains a "Bubble Sort" sorting function
********************************************************************/
class Sort
{
	public:
		template <class T, class O>
		void operator() (T& object, const O& compare) {
			auto iterb = object.begin();  
			auto itere = --(object.end()); 
			try {
				for (auto iteri = iterb; iteri != itere; ++iteri) {
					for (auto iterj = itere; iterj != iteri; --iterj) {
						if (compare(*iteri, *iterj)) {
							// Swap if needed 
							auto temp = *iteri;
							*iteri = *iterj;
							*iterj = temp;
						}
					}
				}
			}
			catch (out_of_range& ex) {
				throw;
			}
			catch (exception& ex) {
				throw;
			}
		}
};