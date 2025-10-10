# TODO - UE GAS 네트워크 포트폴리오

## 진행 상태 범례
- ✅ 완료
- 🔄 진행 중
- ⏳ 대기 중
- ❌ 보류/취소

---

## Phase 1: GAS 프레임워크 기본 구조 ✅

### 1.1 AbilitySystemComponent 설정 ✅
- ✅ PlayerState에 ASC 추가
- ✅ IAbilitySystemInterface 구현
- ✅ 네트워크 복제 설정 (DOREPLIFETIME)
- ✅ NetUpdateFrequency 최적화 (100Hz)

### 1.2 멀티플레이 초기화 로직 ✅
- ✅ PossessedBy 구현 (서버)
- ✅ OnRep_PlayerState 구현 (클라이언트)
- ✅ InitAbilityActorInfo 호출
- ✅ nullptr 안전 체크 추가

---

## Phase 2: AttributeSet 구현 ⏳

### 2.1 AttributeSet 클래스 생성
- ⏳ MyAttributeSet 클래스 생성
- ⏳ 기본 속성 정의
  - Health (체력)
  - MaxHealth (최대 체력)
  - Mana (마나)
  - MaxMana (최대 마나)
  - Stamina (스태미나)
  - MaxStamina (최대 스태미나)
- ⏳ 속성 복제 설정
- ⏳ 속성 변경 콜백 구현

### 2.2 AttributeSet을 PlayerState에 통합
- ⏳ PlayerState에 AttributeSet 추가
- ⏳ 생성자에서 AttributeSet 초기화
- ⏳ GetAttributeSet 함수 구현

---

## Phase 3: GameplayAbility 구현 ⏳

### 3.1 기본 Ability 클래스
- ⏳ MyGameplayAbility 베이스 클래스 생성
- ⏳ ActivateAbility 구현
- ⏳ EndAbility 구현
- ⏳ Ability 취소 로직

### 3.2 테스트용 Ability
- ⏳ 기본 공격 Ability (예: 펀치)
- ⏳ Animation Montage 연동 테스트
- ⏳ Cooldown 적용
- ⏳ Cost(Mana/Stamina) 적용

### 3.3 Ability 등록 및 부여
- ⏳ 캐릭터 생성 시 Ability 자동 부여
- ⏳ Ability 입력 바인딩 시스템

---

## Phase 4: GameplayEffect 구현 ⏳

### 4.1 기본 Effect
- ⏳ Instant Effect (즉시 적용)
- ⏳ Duration Effect (지속 시간)
- ⏳ Infinite Effect (무한 지속)

### 4.2 테스트용 Effect
- ⏳ 데미지 Effect
- ⏳ 힐 Effect
- ⏳ 버프/디버프 Effect

---

## Phase 5: Gameplay Tags 시스템 ⏳

### 5.1 Tag 구조 설계
- ⏳ 프로젝트 Tag 계층 구조 설계
  - Ability.Attack.Melee
  - Ability.Skill.Active
  - State.Dead
  - State.Stunned
  - etc.

### 5.2 Tag 설정
- ⏳ DefaultGameplayTags.ini 설정
- ⏳ C++에서 Native Tag 정의

---

## Phase 6: 입력 시스템 통합 ⏳

### 6.1 Enhanced Input 연동
- ⏳ Input Action 생성
- ⏳ Input Mapping Context 설정
- ⏳ Ability 입력 바인딩

### 6.2 Ability 활성화
- ⏳ 키 입력으로 Ability 실행
- ⏳ Ability Queue 시스템 (선택)

---

## Phase 7: UI 연동 ⏳

### 7.1 AttributeSet UI 바인딩
- ⏳ 체력바 Widget
- ⏳ 마나바 Widget
- ⏳ AttributeSet 변경 시 UI 업데이트

### 7.2 Ability UI
- ⏳ Cooldown 표시
- ⏳ Ability 아이콘 UI
- ⏳ Cost 표시

---

## Phase 8: 네트워크 테스트 및 최적화 ⏳

### 8.1 멀티플레이 테스트
- ⏳ 로컬 멀티플레이 테스트 (2-4 플레이어)
- ⏳ Dedicated Server 테스트
- ⏳ 복제 검증

### 8.2 최적화
- ⏳ 네트워크 프로파일링
- ⏳ Replication 모드 최적화
- ⏳ Bandwidth 최적화

---

## Phase 9: 고급 기능 (선택) ⏳

### 9.1 Gameplay Cue
- ⏳ 타격 이펙트
- ⏳ 스킬 이펙트
- ⏳ 사운드 통합

### 9.2 Ability Task
- ⏳ Custom Ability Task 구현
- ⏳ 비동기 작업 처리

### 9.3 Targeting System
- ⏳ Target Actor 구현
- ⏳ 범위 스킬 타겟팅

---

## Phase 10: 문서화 및 포트폴리오 준비 ⏳

### 10.1 코드 문서화
- ⏳ 주요 클래스 주석 추가
- ⏳ 함수 설명 추가
- ⏳ README 업데이트

### 10.2 포트폴리오 자료
- ⏳ 시연 영상 제작
- ⏳ 기능 설명 문서
- ⏳ 코드 하이라이트 정리

---

## 버그 및 이슈 트래킹

### 현재 이슈
_이슈 없음_

### 해결된 이슈
- ✅ ASC 초기화 타이밍 문제 (PostInitializeComponents → PossessedBy/OnRep_PlayerState)
- ✅ nullptr 크래시 방지 체크 추가

---

## 메모 및 아이디어

### 구현 아이디어
- 대시 스킬
- 이동 관련 Root Motion Ability
- 콤보 시스템
- 파티 시스템 (멀티플레이)

### 참고 사항
- GAS는 리플렉션 시스템을 많이 사용하므로 빌드 시간이 길 수 있음
- AttributeSet 변경 시 항상 PreAttributeChange/PostGameplayEffectExecute 사용
- 멀티플레이 테스트는 초기부터 자주 수행할 것

---

**최종 업데이트**: 2025-10-10
**다음 목표**: Phase 2 - AttributeSet 구현
