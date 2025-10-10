# GAS 프레임워크 설계 문서

## 프로젝트 개요
언리얼 엔진 GAS(Gameplay Ability System) 프레임워크와 멀티플레이 기능을 중심으로 한 포트폴리오 프로젝트

---

## 아키텍처 설계

### AbilitySystemComponent 위치 결정

**선택: PlayerState에 ASC 배치**

#### 이유
1. **멀티플레이 최적화**: PlayerState는 자동으로 클라이언트 간 복제됨
2. **캐릭터 리스폰 안전**: 캐릭터가 죽어도 어빌리티와 속성 유지
3. **Possess 독립적**: 캐릭터 교체 시에도 어빌리티 데이터 유지
4. **Epic Games 권장 방식**: 멀티플레이 게임의 표준 구현 방식

#### 대안 (채택하지 않음)
- Character에 ASC 배치: AI/NPC용으로는 적합하나, 플레이어는 리스폰 시 재설정 필요

---

## 구현 상세

### 1. MyPlayerState (ASC 소유자)

**파일**: `Source/UE_GAS_Net_PortFolio/PlayerState/MyPlayerState.h/cpp`

#### 주요 기능
- `UAbilitySystemComponent` 생성 및 소유
- `IAbilitySystemInterface` 구현
- 네트워크 복제 설정

#### 핵심 코드
```cpp
class AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "GAS")
    TObjectPtr<UAbilitySystemComponent> ASC;

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    // 네트워크 업데이트 빈도 100Hz 설정 (GAS 최적화)
    NetUpdateFrequency = 100.0f;
};
```

#### 네트워크 복제
- `DOREPLIFETIME(AMyPlayerState, ASC)` - ASC 자동 복제

---

### 2. MyPlayer (Avatar 역할)

**파일**: `Source/UE_GAS_Net_PortFolio/Character/MyPlayer.h/cpp`

#### 주요 기능
- PlayerState의 ASC를 Avatar로 등록
- 서버/클라이언트 각각의 초기화 타이밍 처리

#### ASC 초기화 전략

**서버 초기화**: `PossessedBy()`
```cpp
void AMyPlayer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    AMyPlayerState* State = Cast<AMyPlayerState>(GetPlayerState());
    if (!State) return;
    if (!State->GetAbilitySystemComponent()) return;

    // Owner = PlayerState, Avatar = this(Character)
    State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, this);
}
```

**클라이언트 초기화**: `OnRep_PlayerState()`
```cpp
void AMyPlayer::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AMyPlayerState* State = Cast<AMyPlayerState>(GetPlayerState());
    if (!State) return;
    if (!State->GetAbilitySystemComponent()) return;

    State->GetAbilitySystemComponent()->InitAbilityActorInfo(State, this);
}
```

#### 초기화 타이밍

| 환경 | 함수 | 호출 시점 | PlayerState 보장 |
|------|------|----------|-----------------|
| 서버 | `PossessedBy` | 컨트롤러가 캐릭터 포제스 | ✅ |
| 클라이언트 | `OnRep_PlayerState` | PlayerState 복제 완료 | ✅ |

**중요**: `PostInitializeComponents`는 PlayerState가 아직 없을 수 있어 사용하지 않음

---

## InitAbilityActorInfo 파라미터 설명

```cpp
ASC->InitAbilityActorInfo(OwnerActor, AvatarActor);
```

- **OwnerActor**: ASC를 소유한 액터 (PlayerState)
  - 데이터 저장소 역할
  - 네트워크 복제 주체

- **AvatarActor**: 실제 물리적 표현 (Character)
  - Animation Montage 재생 대상
  - Gameplay Cue 생성 위치
  - 타겟팅 기준점

---

## 네트워크 최적화

### PlayerState 설정
- `NetUpdateFrequency = 100.0f`
- PlayerState 기본값이 낮아 GAS에 부족할 수 있어 증가

### ASC 복제 모드
- 현재: 기본 복제 모드 사용
- 향후: `EGameplayEffectReplicationMode::Mixed` 고려 가능

---

## 다음 단계

### 즉시 구현 필요
1. ✅ ~~PlayerState에 ASC 생성~~
2. ✅ ~~멀티플레이 초기화 로직 구현~~
3. ⏳ AttributeSet 추가
4. ⏳ 기본 GameplayAbility 구현
5. ⏳ GameplayEffect 구현

### 향후 계획
- Gameplay Tags 시스템 구축
- Ability 입력 바인딩
- UI와 AttributeSet 연동
- 네트워크 최적화 및 테스트

---

## 참고 자료

- [GAS Documentation](https://docs.unrealengine.com/en-US/gameplay-ability-system-for-unreal-engine/)
- Epic Games 멀티플레이 샘플 프로젝트
- GASShooter (커뮤니티 샘플)

---

**최종 업데이트**: 2025-10-10
**작성자**: Claude Code Assistant
