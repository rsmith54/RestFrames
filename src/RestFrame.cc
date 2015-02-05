#include "RestFrames/RestFrame.hh"

using namespace std;

namespace RestFrames {

  ///////////////////////////////////////////////
  // RestFrame class methods
  ///////////////////////////////////////////////
  int RestFrame::m_class_key = 0;

  RestFrame::RestFrame(const string& sname, const string& stitle, int ikey){
    Init(sname, stitle);
    m_Key = ikey;
  }

  RestFrame::RestFrame(const string& sname, const string& stitle){
    Init(sname, stitle);
    m_Key = GenKey();
  }

  RestFrame::~RestFrame(){
    ClearFrame();
  }

  void RestFrame::Init(const string& sname, const string& stitle){
    m_Name = sname;
    m_Title = stitle;
    m_Body   = false;
    m_Mind   = false;
    m_Spirit = false;
    m_ParentLinkPtr = nullptr;
  }

  int RestFrame::GenKey(){
    int newkey = m_class_key;
    m_class_key++;
    return newkey;
  }

  void RestFrame::ClearFrame(){
    m_Body = false;
    m_Mind = false;
    m_Spirit = false;
    //m_ParentLinkPtr = nullptr;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	delete m_ChildLinks[i];
	m_ChildLinks[i] = nullptr;
      }
    }
    m_ChildLinks.clear();
  }
  
  bool RestFrame::IsSoundBody() const {
    m_Body = true;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(!m_ChildLinks[i]){
	m_Body = false;
	break;
      }
      if(!m_ChildLinks[i]->GetChildFrame()){
	m_Body = false;
	break;
      }
    }
    return m_Body;
  }

  bool RestFrame::IsSoundBodyRecursive() const {
    bool child_body = true;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(!m_ChildLinks[i]) continue;
      if(!m_ChildLinks[i]->GetChildFrame()) continue;
      child_body = m_ChildLinks[i]->GetChildFrame()->IsSoundBodyRecursive();
    }
    return IsSoundBody() && child_body;
  }

  bool RestFrame::IsSoundMind() const {
    return m_Mind;
  }

  bool RestFrame::IsSoundMindRecursive() const {
    bool child_mind = true;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(!m_ChildLinks[i]) continue;
      if(!m_ChildLinks[i]->GetChildFrame()) continue;
      child_mind = m_ChildLinks[i]->GetChildFrame()->IsSoundMindRecursive();
    }
    return IsSoundMind() && child_mind;
  }

  bool RestFrame::IsSoundSpirit() const {
    return m_Spirit;
  }

  bool RestFrame::IsSoundSpiritRecursive() const {
    bool child_spirit = true;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(!m_ChildLinks[i]) continue;
      if(!m_ChildLinks[i]->GetChildFrame()) continue;
      child_spirit = m_ChildLinks[i]->GetChildFrame()->IsSoundSpiritRecursive();
    }
    return IsSoundSpirit() && child_spirit;
  }

  bool RestFrame::IsSame(const RestFrame& frame) const {
    return IsSame(&frame);
  }
     
  bool RestFrame::IsSame(const RestFrame* framePtr) const {
    if(!framePtr) return false;
    if(m_Key == framePtr->GetKey()) return true;
    return false;
  }

  int RestFrame::GetKey() const {
    return m_Key;
  }

  string RestFrame::GetName() const {
    return m_Name;
  }

  string RestFrame::GetTitle() const {
    return m_Title;
  }

  FrameType RestFrame::GetType() const { 
    return m_Type; 
  }

  bool RestFrame::IsVisibleFrame() const { 
    return m_Type == FVisible; 
  }

  bool RestFrame::IsInvisibleFrame() const { 
    return m_Type == FInvisible; 
  }

  bool RestFrame::IsDecayFrame() const { 
    return m_Type == FDecay; 
  }

  bool RestFrame::IsLabFrame() const { 
    return m_Type == FLab; 
  }

  bool RestFrame::IsRFrame() const { 
    return m_Ana == FReco; 
  }

  bool RestFrame::IsGFrame() const { 
    return m_Ana == FGen; 
  }

  void RestFrame::RemoveChild(const RestFrame* framePtr){
    m_Body = false;
    m_Mind = false;
    m_Spirit = false;
    int index = GetChildIndex(framePtr);
    RemoveChildIndex(index);
    if(index < 0) return;
    if(m_ChildLinks[index]){
      delete m_ChildLinks[index];
      m_ChildLinks[index] = nullptr;
    }
    m_ChildLinks.erase(m_ChildLinks.begin()+index);
  }

  void RestFrame::RemoveChildIndex(int i){
    m_Body = false;
    m_Mind = false;
    m_Spirit = false;
    if(i < 0 || i >= GetNChildren()) return;
    if(m_ChildLinks[i]){
      delete m_ChildLinks[i];
      m_ChildLinks[i] = nullptr;
    }
    m_ChildLinks.erase(m_ChildLinks.begin()+i);
  }

  void RestFrame::RemoveChildren(){
    m_Body = false;
    m_Mind = false;
    m_Spirit = false;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++) RemoveChildIndex(i);
    m_ChildLinks.clear();
  }

  //////////////////////////////
  //Tree construction functions
  //////////////////////////////

  void RestFrame::SetParentLink(FrameLink* linkPtr){
    if(m_Type != FLab) m_ParentLinkPtr = linkPtr;
  }

  void RestFrame::AddChildFrame(RestFrame& frame){
    AddChildFrame(&frame);
  }
  
  void RestFrame::AddChildFrame(RestFrame* framePtr){
    m_Body = false;
    m_Mind = false;
    m_Spirit = false;
    if(!framePtr) return;
    if(framePtr->IsLabFrame()) return;
    if(GetChildIndex(framePtr) >= 0) return;
  
    FrameLink* linkPtr = new FrameLink();
    linkPtr->SetParentFrame(this);
    linkPtr->SetChildFrame(framePtr);
    framePtr->SetParentLink(linkPtr);
    m_ChildLinks.push_back(linkPtr);
  }

  int RestFrame::GetNChildren() const { 
    return int(m_ChildLinks.size()); 
  }

  int RestFrame::GetChildIndex(const RestFrame* framePtr) const {
    if(!framePtr) return -1;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* childPtr = m_ChildLinks[i]->GetChildFrame();
	if(childPtr){
	  if(childPtr->IsSame(framePtr)){
	    return i;
	  }
	}
      }
    }
    return -1;
  }

  RestFrame* RestFrame::GetChildFrame(int i) const {
    int Nchild = GetNChildren();
    if(i >= Nchild || i < 0) return nullptr;
    if(m_ChildLinks[i]){
      return m_ChildLinks[i]->GetChildFrame();
    }
    return nullptr;
  }

  const RestFrame* RestFrame::GetLabFrame() const{
    if(m_Type == FLab) return this;
    if(!m_ParentLinkPtr) return nullptr;
    RestFrame* parentPtr = m_ParentLinkPtr->GetParentFrame();
    if(parentPtr) return parentPtr->GetLabFrame();
    return nullptr;
  } 

  RestFrameList* RestFrame::GetListFrames(){
    RestFrameList* framesPtr = new RestFrameList();
    framesPtr->Add(this);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) framePtr->FillListFramesRecursive(framesPtr);
      }
    }
    return framesPtr;
  }

  RestFrameList* RestFrame::GetListFramesType(FrameType type){
    RestFrameList* framesPtr = new RestFrameList();
    if(m_Type == type) framesPtr->Add(this);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) framePtr->FillListFramesTypeRecursive(type, framesPtr);
      }
    }
    return framesPtr;
  }

  RestFrameList* RestFrame::GetListFramesType(const vector<FrameType>& types){
    RestFrameList* framesPtr = new RestFrameList();
    int Nchild = GetNChildren();
    int Ntype = int(types.size());
    for(int i = 0; i < Ntype; i++){
      if(m_Type == types[i]) framesPtr->Add(this);
    }
    for(int j = 0; j < Nchild; j++){
      if(m_ChildLinks[j]){
	RestFrame* framePtr = m_ChildLinks[j]->GetChildFrame();
	if(framePtr){
	  for(int i = 0; i < Ntype; i++){
	    framePtr->FillListFramesTypeRecursive(types[i], framesPtr);
	  }
	}
      }
    }
    return framesPtr;
  }

  RestFrameList* RestFrame::GetListVisibleFrames(){
    return GetListFramesType(FVisible);
  }

  RestFrameList* RestFrame::GetListInvisibleFrames(){
    return GetListFramesType(FInvisible);
  }

  void RestFrame::FillListFramesRecursive(RestFrameList* framesPtr){
    framesPtr->Add(this);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) framePtr->FillListFramesRecursive(framesPtr);
      }
    }
  }
  
  void RestFrame::FillListFramesTypeRecursive(FrameType type, RestFrameList* framesPtr){
    if(m_Type == type) framesPtr->Add(this);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) framePtr->FillListFramesTypeRecursive(type, framesPtr);
      }
    }
  }

  //
  // Recursive checks of tree integrity
  //
  bool RestFrame::IsCircularTree(vector<int>* KEYS) const {
    int Nkey = KEYS->size();
  
    for(int i = 0; i < Nkey; i++){
      if((*KEYS)[i] == m_Key){
	cout << endl << "Warning: reference frame ";
	cout << m_Name.c_str() << " appears more than once in tree" << endl;
	return true;
      }
    }
    KEYS->push_back(m_Key);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) if(framePtr->IsCircularTree(KEYS)) return true;
      }
    }
    return false;
  }

  bool RestFrame::IsConsistentAnaTree(AnaType ana) const {
    if(ana != m_Ana) return false;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      if(m_ChildLinks[i]){
	RestFrame* framePtr = m_ChildLinks[i]->GetChildFrame();
	if(framePtr) if(!framePtr->IsConsistentAnaTree(ana)) return false;
      }
    }
    return true;
  }

  bool RestFrame::FindPathToFrame(const RestFrame* framePtr, vector<FrameLink*>* linksPtr, 
				  vector<int>* linkSignsPtr, const RestFrame *prevPtr) const {
    if(IsSame(framePtr)) return true;
  
    vector<FrameLink*> try_links;
    vector<int> try_signs;

    try_links.push_back(m_ParentLinkPtr);
    try_signs.push_back(1);
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      try_links.push_back(m_ChildLinks[i]);
      try_signs.push_back(-1);
    }
    for(int i = 0; i < Nchild+1; i++){
      if(!try_links[i]) continue;
      RestFrame* nextPtr;
      if(try_signs[i] > 0) nextPtr = try_links[i]->GetParentFrame();
      else nextPtr = try_links[i]->GetChildFrame();
      if(nextPtr->IsSame(prevPtr)) continue;
      linksPtr->push_back(try_links[i]);
      linkSignsPtr->push_back(try_signs[i]);
      if(nextPtr->FindPathToFrame(framePtr,linksPtr,linkSignsPtr,this)) return true;
      linksPtr->pop_back();
      linkSignsPtr->pop_back();
    }
    return false;
  }

  //////////////////////////////
  // Analysis functions
  //////////////////////////////
  void RestFrame::SetFourVector(const TLorentzVector& V, const RestFrame* framePtr){
    m_P.SetVectM(V.Vect(),V.M());
    m_ProdFramePtr = framePtr;  
  }

  double RestFrame::GetMass() const {
    return m_P.M();
  }

  double RestFrame::GetCosDecayAngle() const {
    if(m_ChildLinks.size() <= 0) return 0.;
    if(!m_ParentLinkPtr) return 0.;
    TVector3 V1 = m_ParentLinkPtr->GetBoostVector().Unit();
    TVector3 V2 = m_ChildLinks[0]->GetChildFrame()->GetFourVector(this).Vect().Unit();
    return V1.Dot(V2);
  }
 
  double RestFrame::GetDeltaPhiDecayAngle(TVector3 axis) const {
    if(m_ChildLinks.size() <= 0) return 0.;
    if(!m_ParentLinkPtr) return 0.;
    TLorentzVector Pthis = GetFourVector(GetProductionFrame());
    TLorentzVector Pchild = m_ChildLinks[0]->GetChildFrame()->GetFourVector(GetProductionFrame());

    TVector3 boost_par = Pthis.BoostVector();
    boost_par = boost_par.Dot(axis.Unit())*axis.Unit();
    Pthis.Boost(-boost_par);
    Pchild.Boost(-boost_par);
    TVector3 boost_perp = Pthis.BoostVector();
    Pchild.Boost(-boost_perp);

    TVector3 V = Pchild.Vect();
    V = V - V.Dot(axis.Unit())*axis.Unit();
    return V.Angle(boost_perp);
  }
 
  double RestFrame::GetDeltaPhiVisible(TVector3 axis, const RestFrame* framePtr) const {
    if(GetNChildren() != 2) return 0.;
    if(!framePtr) framePtr = GetLabFrame();
    TLorentzVector Pthis = GetFourVector(framePtr);
    TLorentzVector P1 = m_ChildLinks[0]->GetChildFrame()->GetVisibleFourVector(framePtr);
    TLorentzVector P2 = m_ChildLinks[1]->GetChildFrame()->GetVisibleFourVector(framePtr);

    TVector3 boost_par = Pthis.BoostVector();
    boost_par = boost_par.Dot(axis.Unit())*axis.Unit();
    Pthis.Boost(-boost_par);
    P1.Boost(-boost_par);
    P2.Boost(-boost_par);
    TVector3 boost_perp = Pthis.BoostVector();
    P1.Boost(-boost_perp);
    P2.Boost(-boost_perp);

    TVector3 V1 = P1.Vect();
    TVector3 V2 = P2.Vect();
    V1 = V1 - V1.Dot(axis.Unit())*axis.Unit();
    V2 = V2 - V2.Dot(axis.Unit())*axis.Unit();
   
    return V1.Angle(V2);
  }

double RestFrame::GetDeltaPhiBoostVisible(TVector3 axis, const RestFrame* framePtr) const {
    if(!framePtr) framePtr = GetLabFrame();
    TLorentzVector Pvis = GetVisibleFourVector(framePtr);
    TLorentzVector Pthis = GetFourVector(framePtr);

    TVector3 boost_par = Pthis.BoostVector();
    boost_par = boost_par.Dot(axis.Unit())*axis.Unit();
    Pthis.Boost(-boost_par);
    Pvis.Boost(-boost_par);
    TVector3 boost_perp = Pthis.BoostVector();
    Pvis.Boost(-boost_perp);

    TVector3 V = Pvis.Vect();
    V = V - V.Dot(axis.Unit())*axis.Unit();
   
    return V.Angle(boost_perp);
  }

  double RestFrame::GetVisibleShape() const {
    if(GetNChildren() != 2) return 0.;
    TVector3 P1 = m_ChildLinks[0]->GetChildFrame()->GetVisibleFourVector(this).Vect();
    TVector3 P2 = m_ChildLinks[1]->GetChildFrame()->GetVisibleFourVector(this).Vect();
    if(P1.Mag()+P2.Mag() > 0.) return sqrt(pow(P1.Mag()+P2.Mag(),2.)-(P1-P2).Mag2())/(P1.Mag()+P2.Mag());
    else return 0.;
  }
 
  double RestFrame::GetTransverseVisibleShape(TVector3 axis, const RestFrame* framePtr) const {
    if(GetNChildren() != 2) return 0.;
    if(!framePtr) framePtr = GetLabFrame();
    TLorentzVector Pthis = GetFourVector(framePtr);
    TLorentzVector P1 = m_ChildLinks[0]->GetChildFrame()->GetVisibleFourVector(framePtr);
    TLorentzVector P2 = m_ChildLinks[1]->GetChildFrame()->GetVisibleFourVector(framePtr);

    TVector3 boost_par = Pthis.BoostVector();
    boost_par = boost_par.Dot(axis.Unit())*axis.Unit();
    Pthis.Boost(-boost_par);
    P1.Boost(-boost_par);
    P2.Boost(-boost_par);
    TVector3 boost_perp = Pthis.BoostVector();
    P1.Boost(-boost_perp);
    P2.Boost(-boost_perp);

    TVector3 V1 = P1.Vect();
    TVector3 V2 = P2.Vect();
    V1 = V1 - V1.Dot(axis.Unit())*axis.Unit();
    V2 = V2 - V2.Dot(axis.Unit())*axis.Unit();

    if(V1.Mag()+V2.Mag() > 0.) return sqrt(pow(V1.Mag()+V2.Mag(),2.)-(V1-V2).Mag2())/(P1.P()+P2.P());
    else return 0.;
  }

  TLorentzVector RestFrame::GetFourVector(const RestFrame& frame) const {
    return GetFourVector(&frame);
  }
  TLorentzVector RestFrame::GetFourVector(const RestFrame* framePtr) const {
    TLorentzVector V(0.,0.,0.,0.);
    if(!framePtr) return V;
 
    V.SetVectM(m_P.Vect(),m_P.M());
    if(framePtr->IsSame(m_ProdFramePtr)) return V;

    vector<FrameLink*>* linksPtr = new vector<FrameLink*>;
    vector<int>* linkSignsPtr = new vector<int>;
    if(!m_ProdFramePtr->FindPathToFrame(framePtr,linksPtr,linkSignsPtr,nullptr)) return V;
  
    int Nlink = linksPtr->size();
    for(int i = 0; i < Nlink; i++){
      V.Boost((*linkSignsPtr)[i]*(*linksPtr)[i]->GetBoostVector());
    }
    delete linksPtr;
    delete linkSignsPtr;
    return V;
  }

  TLorentzVector RestFrame::GetVisibleFourVector(const RestFrame& frame) const {
    return GetVisibleFourVector(&frame);
  }
  TLorentzVector RestFrame::GetVisibleFourVector(const RestFrame* framePtr) const {
    TLorentzVector V(0.,0.,0.,0.);
    if(!framePtr || !m_Spirit) return V;
    int Nc = GetNChildren();
    for(int c = 0; c < Nc; c++){
      RestFrameList* framesPtr = m_ChildLinks[c]->GetChildFrame()->GetListVisibleFrames();
      int Nf = framesPtr->GetN();
      for(int f = 0; f < Nf; f++) V += framesPtr->Get(f)->GetFourVector(framePtr);
      delete framesPtr;
    }
    return V;
  }
  TLorentzVector RestFrame::GetInvisibleFourVector(const RestFrame& frame) const {
    return GetInvisibleFourVector(&frame);
  }
  TLorentzVector RestFrame::GetInvisibleFourVector(const RestFrame* framePtr) const {
    TLorentzVector V(0.,0.,0.,0.);
    if(!framePtr || !m_Spirit) return V;
    int Nc = GetNChildren();
    for(int c = 0; c < Nc; c++){
      RestFrameList* framesPtr = m_ChildLinks[c]->GetChildFrame()->GetListInvisibleFrames();
      int Nf = framesPtr->GetN();
      for(int f = 0; f < Nf; f++) V += framesPtr->Get(f)->GetFourVector(framePtr);
      delete framesPtr;
    }
    return V;
  }
  double RestFrame::GetEnergy(const RestFrame& frame) const {
    return GetFourVector(&frame).E();
  }
  double RestFrame::GetEnergy(const RestFrame* framePtr) const {
    return GetFourVector(framePtr).E();
  }
  double RestFrame::GetMomentum(const RestFrame& frame) const {
    return GetFourVector(&frame).P();
  }
  double RestFrame::GetMomentum(const RestFrame *framePtr) const {
    return GetFourVector(framePtr).P();
  }

  double RestFrame::GetScalarVisibleMomentum() const {
    if(GetNChildren() != 2) return 0.;
    TLorentzVector P1 = m_ChildLinks[0]->GetChildFrame()->GetVisibleFourVector(this);
    TLorentzVector P2 = m_ChildLinks[1]->GetChildFrame()->GetVisibleFourVector(this);
    return P1.P() + P2.P();
  }
  double RestFrame::GetTransverseScalarVisibleMomentum(TVector3 axis, 
						       const RestFrame* framePtr) const {
    if(GetNChildren() != 2) return 0.;
    if(!framePtr) framePtr = GetLabFrame();
    TLorentzVector Pthis = GetFourVector(framePtr);
    TLorentzVector P1 = m_ChildLinks[0]->GetChildFrame()->GetVisibleFourVector(framePtr);
    TLorentzVector P2 = m_ChildLinks[1]->GetChildFrame()->GetVisibleFourVector(framePtr);

    TVector3 boost_par = Pthis.BoostVector();
    boost_par = boost_par.Dot(axis.Unit())*axis.Unit();
    Pthis.Boost(-boost_par);
    P1.Boost(-boost_par);
    P2.Boost(-boost_par);
    TVector3 boost_perp = Pthis.BoostVector();
    P1.Boost(-boost_perp);
    P2.Boost(-boost_perp);

    TVector3 V1 = P1.Vect();
    TVector3 V2 = P2.Vect();
    V1 = V1 - V1.Dot(axis.Unit())*axis.Unit();
    V2 = V2 - V2.Dot(axis.Unit())*axis.Unit();

    return V1.Mag()+V2.Mag();
  }

  int RestFrame::GetFrameDepth(const RestFrame& frame) const {
    return GetFrameDepth(&frame);
  }
  int RestFrame::GetFrameDepth(const RestFrame* framePtr) const {
    if(!framePtr) return -1;
    if(IsSame(framePtr)) return 0.;
    int Nchild = GetNChildren();
    for(int i = 0; i < Nchild; i++){
      int depth = m_ChildLinks[i]->GetChildFrame()->GetFrameDepth(framePtr);
      if(depth >= 0) return depth+1;
    }
    return -1;
  }

  const RestFrame* RestFrame::GetFrameAtDepth(int depth, const RestFrame& frame) const {
    return GetFrameAtDepth(depth, &frame);
  }
  const RestFrame* RestFrame::GetFrameAtDepth(int depth, const RestFrame* framePtr) const {
    if(!framePtr || depth < 1) return nullptr;
    int N = GetNChildren();
    for(int i = 0; i < N; i++){
      RestFrame* childPtr = GetChildFrame(i);
      RestFrameList* framesPtr = childPtr->GetListFrames();
      if(framesPtr->Contains(framePtr)){
	delete framesPtr;
	if(depth == 1) return childPtr;
	else return childPtr->GetFrameAtDepth(depth-1,framePtr);
      }
      delete framesPtr;
    }
    return nullptr;
  }

  double RestFrame::GetDeltaPhiDecayPlanes(const RestFrame& frame) const {
    return GetDeltaPhiDecayPlanes(&frame);
  }
  double RestFrame::GetDeltaPhiDecayPlanes(const RestFrame* framePtr) const {
    if(!framePtr) return 0.;
    if(!m_ParentLinkPtr) return 0.;
    TVector3 vNorm_frame = framePtr->GetDecayPlaneNormalVector();
    TVector3 vNorm_this = GetDecayPlaneNormalVector();
    double dphi = vNorm_this.Angle(vNorm_frame);
    if(m_ParentLinkPtr->GetBoostVector().Dot(vNorm_frame) < 0. && dphi > 0.){
      dphi = TMath::Pi()*2. - dphi;
    }
    return dphi;
  }
  TVector3 RestFrame::GetDecayPlaneNormalVector() const {
    TVector3 V(0.,0.,0.);
    if(m_ChildLinks.size() < 1) return V;
    if(!m_ParentLinkPtr) return V;
    TVector3 V1 = m_ParentLinkPtr->GetBoostVector().Unit();
    TVector3 V2 = m_ChildLinks[0]->GetChildFrame()->GetFourVector(this).Vect().Unit();
    return V1.Cross(V2).Unit();
  }

  const RestFrame* RestFrame::GetProductionFrame() const {
    return m_ProdFramePtr;
  }

  TVector3 RestFrame::GetBoostInParentFrame() const{
    TVector3 V(0.,0.,0.);
    if(!m_ParentLinkPtr) return V;
    return m_ParentLinkPtr->GetBoostVector();
  }

  double RestFrame::GetGammaInParentFrame() const{
    TVector3 vbeta = GetBoostInParentFrame();
    double beta = min(1.,vbeta.Mag());
    return 1./sqrt(1.-beta*beta);
  }

}